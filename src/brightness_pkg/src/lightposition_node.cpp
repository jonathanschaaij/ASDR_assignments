#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"

using namespace std::chrono_literals;

class LightPositionReader : public rclcpp::Node
{
public:
  LightPositionReader()
      : Node("lightposition_node"), count_(0)
  {

    RCLCPP_INFO(this->get_logger(), "Starting light position reader");
    publisher_ = this->create_publisher<std_msgs::msg::String>("lightPosition", 10);
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10, std::bind(&LightPositionReader::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg) const
  {
    if (!msg)
    {
      RCLCPP_ERROR(this->get_logger(), "Received null message");
      return;
    }
    // Step 1: Convert the input image to grayscale
    const int num_channels = 3;
    int width = msg->width;
    int height = msg->height;
    unsigned char *gray_image = new unsigned char[width * height];
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        int index = (i * width + j) * num_channels;
        unsigned char red = msg->data[index];
        unsigned char green = msg->data[index + 1];
        unsigned char blue = msg->data[index + 2];
        gray_image[i * width + j] = 0.299 * red + 0.587 * green + 0.114 * blue;
      }
    }

    // Step 2: Apply a threshold to the grayscale image
    const int threshold_value = 100;
    unsigned char *binary_image = new unsigned char[width * height];
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        if (gray_image[i * width + j] > threshold_value)
        {
          binary_image[i * width + j] = 255;
        }
        else
        {
          binary_image[i * width + j] = 0;
        }
      }
    }

    // Step 3: Compute the center of gravity (COG) of the white pixels
    double x_cog = 0.0, y_cog = 0.0;
    int num_white_pixels = 0;
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        if (binary_image[i * width + j] == 255)
        {
          x_cog += j;
          y_cog += i;
          num_white_pixels++;
        }
      }
    }
    x_cog /= num_white_pixels;
    y_cog /= num_white_pixels;

    RCLCPP_INFO(this->get_logger(), "COG (x,y) = (%0.2f, %0.2f)", x_cog, y_cog);

    auto message = std_msgs::msg::String();
    message.data = "Got message";
    publisher_->publish(message);
  };
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LightPositionReader>());
  rclcpp::shutdown();
  return 0;
}
