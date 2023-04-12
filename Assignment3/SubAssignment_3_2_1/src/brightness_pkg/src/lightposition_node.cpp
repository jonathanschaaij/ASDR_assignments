#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "asdfr_interfaces/msg/point2.hpp"

using namespace std::chrono_literals;

class LightPositionReader : public rclcpp::Node
{
public:
  LightPositionReader()
      : Node("lightposition_node"), count_(0)
  {

    RCLCPP_INFO(this->get_logger(), "Starting light position reader");
    publisher_ = this->create_publisher<std_msgs::msg::String>("lightPosition", 10);

    this->declare_parameter("inputimage", "moving_camera_output");
    inputimage = this->get_parameter("inputimage").get_parameter_value().get<std::string>();
    RCLCPP_INFO(this->get_logger(), "(SET PARAM) Analyzing inputsource: %s", inputimage.c_str());

    this->declare_parameter("threshold", 240.0);
    threshold = this->get_parameter("threshold").get_parameter_value().get<double>();
    RCLCPP_INFO(this->get_logger(), "(SET PARAM) Threshold: %0.2f", threshold);

    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        inputimage, 10, std::bind(&LightPositionReader::topic_callback, this, std::placeholders::_1));

    greyscalepublisher_ = this->create_publisher<sensor_msgs::msg::Image>("grayImage", 10);
    binarypublisher_ = this->create_publisher<sensor_msgs::msg::Image>("binaryImage", 10);
    targetpublisher_ = this->create_publisher<asdfr_interfaces::msg::Point2>("cog_pixels", 10);
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

    // Publish the image to the grayscale topic for verification
    sensor_msgs::msg::Image grayscale_msg;
    grayscale_msg.header.frame_id = "grayscale_camera";
    grayscale_msg.height = height;
    grayscale_msg.width = width;
    grayscale_msg.encoding = "mono8";                                                 // "mono8" is the encoding for an 8-bit grayscale image
    grayscale_msg.step = width;                                                       // Number of bytes per row
    grayscale_msg.data.resize(height * width);                                        // Allocate memory for the image data
    std::copy(gray_image, gray_image + (height * width), grayscale_msg.data.begin()); // Copy the grayscale image data into the message
    greyscalepublisher_->publish(grayscale_msg);

    // Step 2: Apply a threshold to the grayscale image
    unsigned char *binary_image = new unsigned char[width * height * 3];
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        if (gray_image[i * width + j] > threshold)
        {
          binary_image[(i * width + j) * 3] = 255;     // Red channel
          binary_image[(i * width + j) * 3 + 1] = 255; // Green channel
          binary_image[(i * width + j) * 3 + 2] = 255; // Blue channel
        }
        else
        {
          binary_image[(i * width + j) * 3] = 0;     // Red channel
          binary_image[(i * width + j) * 3 + 1] = 0; // Green channel
          binary_image[(i * width + j) * 3 + 2] = 0; // Blue channel
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
        if (binary_image[(i * width + j) * 3] == 255)
        {
          x_cog += j;
          y_cog += i;
          num_white_pixels++;
        }
      }
    }
    if (num_white_pixels == 0)
    {
      // Without bright pixels the COG is the center of the image
      x_cog = width/2;
      y_cog = height/2;
      num_white_pixels = 1;
    } else {
      x_cog /= num_white_pixels;
      y_cog /= num_white_pixels;
    }

    // RCLCPP_INFO(this->get_logger(), "COG (x,y) = (%0.2f, %0.2f)", x_cog, y_cog);

    int x_pos = static_cast<int>(x_cog);
    int y_pos = static_cast<int>(y_cog);
    
    // Draw a red circle around the COG for easy validation
    int radius = 5;
    for (int i = y_pos - radius; i <= y_pos + radius; i++)
    {
      for (int j = x_pos - radius; j <= x_pos + radius; j++)
      {
        if (i >= 0 && i < height && j >= 0 && j < width)
        {
          if ((i - y_pos) * (i - y_pos) + (j - x_pos) * (j - x_pos) <= radius * radius)
          {
            binary_image[i * width * 3 + j * 3] = 255;   // Red channel
            binary_image[i * width * 3 + j * 3 + 1] = 0; // Green channel
            binary_image[i * width * 3 + j * 3 + 2] = 0; // Blue channel
          }
        }
      }
    }

    // Publish the image to the binary topic for verification
    sensor_msgs::msg::Image binary_msg;
    binary_msg.header.frame_id = "binary_camera";
    binary_msg.height = height;
    binary_msg.width = width;
    binary_msg.encoding = "rgb8";                                                          // "rgb8" is the encoding for an 8-bit RGB image
    binary_msg.step = width * 3;                                                           // Number of bytes per row
    binary_msg.data.resize(height * width * 3);                                            // Allocate memory for the image data
    std::copy(binary_image, binary_image + (height * width * 3), binary_msg.data.begin()); // Copy the RGB image data into the message
    binarypublisher_->publish(binary_msg);

    // Publish the COG 
    asdfr_interfaces::msg::Point2 message;
    message.x = (x_cog);
    message.y = (y_cog);
    targetpublisher_->publish(message);
  };
  mutable std::string inputimage;
  mutable double threshold;

  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
  rclcpp::Subscription<asdfr_interfaces::msg::Point2>::SharedPtr pos_subscription_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr greyscalepublisher_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr binarypublisher_;
  rclcpp::Publisher<asdfr_interfaces::msg::Point2>::SharedPtr targetpublisher_;
  mutable float target[2] = {0, 0};
  size_t count_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LightPositionReader>());
  rclcpp::shutdown();
  return 0;
}
