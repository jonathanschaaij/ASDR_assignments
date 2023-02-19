#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

// class MinimalPublisher : public rclcpp::Node
// {
//   public:
//     MinimalPublisher()
//     : Node("minimal_publisher"), count_(0)
//     {
//       publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
//       timer_ = this->create_wall_timer(
//       500ms, std::bind(&MinimalPublisher::timer_callback, this));
//     }

//   private:
//     void timer_callback()
//     {
//       auto message = std_msgs::msg::String();
//       message.data = "Hello, world! " + std::to_string(count_++);
//       RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//       publisher_->publish(message);
//     }
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
//     size_t count_;
// };

class BrightnessReader : public rclcpp::Node
{
public:
  BrightnessReader()
      : Node("brighness_node"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&BrightnessReader::topic_callback, this, std::placeholders::_1));
  }

private:
  // void topic_callback(const std_msgs::msg::String & msg) const
  void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg) const
  {
    if (!msg)
    {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
      return;
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

    RCLCPP_INFO(this->get_logger(), "I got data : B=%0.2f", average_brightness);
  }
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
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
