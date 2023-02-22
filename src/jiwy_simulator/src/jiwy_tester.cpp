#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "asdfr_interfaces/msg/point2.hpp"

using namespace std::chrono_literals;

class JiwyTester : public rclcpp::Node
{
public:
    JiwyTester()
        : Node("jiwytest_node")
    {
        RCLCPP_INFO(this->get_logger(), "Starting Jiwytester");
        publisher_ = this->create_publisher<asdfr_interfaces::msg::Point2>("setpoint", 10);

        timer_ = this->create_wall_timer(
            5000ms, std::bind(&JiwyTester::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message = asdfr_interfaces::msg::Point2();
        message.x = 1;
        message.y = 1;
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<asdfr_interfaces::msg::Point2>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JiwyTester>());
    rclcpp::shutdown();
    return 0;
}
