#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"

using namespace std::chrono_literals;

class BrightnessReader : public rclcpp::Node
{
public:
  BrightnessReader()
      : Node("brightness_node"), count_(0)
  {
    this->declare_parameter("threshold", 80.0);
    threshold =
        this->get_parameter("threshold").get_parameter_value().get<double>();
    RCLCPP_INFO(this->get_logger(), "Starting Threshold: %0.2f", threshold);
    publisher_ = this->create_publisher<std_msgs::msg::String>("lightState", 10);
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&BrightnessReader::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg) const
  {
    if (!msg)
    {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
      return;
    }
    double setThreshold =
        this->get_parameter("threshold").get_parameter_value().get<double>();
    if (setThreshold != threshold)
    {
      RCLCPP_INFO(this->get_logger(), "Threshold changed: %0.2f->%0.2f", threshold, setThreshold);
      threshold = setThreshold;
    }

    double total_brightness = 0.0;
    for (unsigned int i = 0; i < msg->height; i++)
    {
      const uint8_t *row_ptr = &msg->data[i * msg->step];
      for (unsigned int j = 0; j < msg->width; j++)
      {
        uint8_t pixel_value = row_ptr[j];
        total_brightness += pixel_value;
      }
    }
    double average_brightness = total_brightness / (msg->width * msg->height);
    RCLCPP_INFO(this->get_logger(), "Average brightness=%0.2f", average_brightness);

    // Send message when state changed
    auto message = std_msgs::msg::String();
    if (average_brightness > threshold && !lightState)
    {
      lightState = true;
      message.data = "Switched to Light!";
      publisher_->publish(message);
    }
    else if (average_brightness < threshold && lightState)
    {
      lightState = false;
      message.data = "Switched to Dark!";
      publisher_->publish(message);
    }
  }
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  mutable double threshold;
  mutable bool lightState = true;
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  // rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::spin(std::make_shared<BrightnessReader>());
  rclcpp::shutdown();
  return 0;
}
