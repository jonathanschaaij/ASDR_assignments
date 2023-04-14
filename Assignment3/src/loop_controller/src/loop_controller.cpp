#include <cstdio>
#include <memory>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float32.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/image_encodings.hpp"
#include "asdfr_interfaces/msg/point2.hpp" // 2D point (x and y coordinates)
#include "xenomai-ros2-framework/framework/multiCommClass.h"


#include "controller_functions.h"

using std::placeholders::_1;

class LoopController : public rclcpp::Node
{
public:
  LoopController() : Node("loop_controller")
  {

    // Check that this runs on the xenomai thingymajing

    // Subscribe to light_pos node
    cog_subscription = this->create_subscription<asdfr_interfaces::msg::Point2>(
        "cog_pos", 10, std::bind(&LoopController::cog_topic_callback, this, _1));

    // Create 20sim class instance
    // ControllerTilt *tilt_controller = new ControllerTilt();

    // Set up communication parameters

    // int iddp_uParam_PlantData[] = {/* Fill with appropriate values */};
    // int xddp_uParam_Setpoint[] = {/* Fill with appropriate values */};
    // int iddp_yParam_ControlOutput[] = {/* Fill with appropriate values */};
    // int xddp_yParam_Logging[] = {/* Fill with appropriate values */};

    int iddp_uParam_PlantData[] = {0};
    int xddp_uParam_Setpoint[] = {1};
    int iddp_yParam_ControlOutput[] = {0};
    int xddp_yParam_Logging[] = {0};

    // Create communication class instances
    IcoComm *icoComm = new IcoComm(/* Fill with appropriate values */);

    // Create communication class instances
    frameworkComm *controller_uPorts[] = {
        new IDDPComm(5, -1, 1, iddp_uParam_PlantData),
        icoComm};
    frameworkComm *controller_yPorts[] = {
        new IDDPComm(2, 3, 1, iddp_yParam_ControlOutput),
        icoComm};

    // Create wrapper class instance
    runnableClass<ControllerTilt> *controller_runnable = new runnableClass<ControllerTilt>(
        tilt_controller, controller_uPorts, controller_yPorts, 2, 2);

    // // // // // frameworkComm *controller_uPorts[] = {
    // // // // //     new IDDPComm(5, -1, 1, iddp_uParam_PlantData),
    // // // // //     new XDDPComm(10, -1, 1, xddp_uParam_Setpoint)};
    // // // // // frameworkComm *controller_yPorts[] = {
    // // // // //     new IDDPComm(2, 3, 1, iddp_yParam_ControlOutput),
    // // // // //     new XDDPComm(26, 26, 1, xddp_yParam_Logging)};

    // // // // // // Create wrapper class instance
    // // // // // runnableClass<ControllerTilt> *controller_runnable = new runnableClass<ControllerTilt>(
    // // // // //     tilt_controller, controller_uPorts, controller_yPorts, 2, 2);

    RCLCPP_INFO(this->get_logger(), "Starting loop controller");

    // CREATE PARAM AND WRAPPER FOR CONTROLLER
    int iddpcontroller_uParam[] = {0, 1};
    int xddptiltcontroller_uParam[] = {2};
    int xddppancontroller_uParam[] = {3};
    frameworkComm *controller_uPorts[] = {
        new IDDPComm(5, -1, 2, iddpcontroller_uParam),
        new XDDPComm(10, -1, 1, xddptiltcontroller_uParam),
        new XDDPComm(11, -1, 1, xddppancontroller_uParam)};
    int controller_yParam[] = {0, 1};
    int controller_yParam_logging[] = {0};
    frameworkComm *controller_yPorts[] = {
        new IDDPComm(2, 3, 2, controller_yParam)};
    Controller *controller_class = new Controller;
    runnable *controller_runnable = new wrapper<Controller>(
        controller_class, controller_uPorts, controller_yPorts, 3, 1);
    controller_runnable->setSize(4, 2);

    // Init Xenothread for controller
    xenoThread controllerClass(controller_runnable);
    controllerClass.init(1000000, 98, 0);
    controllerClass.enableLogging(true, 26);

    // Start the controller
    controllerClass.start("controller");
  }

private:
  void cog_topic_callback(const asdfr_interfaces::msg::Point2::SharedPtr cog)
  {
    RCLCPP_INFO(this->get_logger(), "Received a new COG: (%f, %f)", cog->x, cog->y);

    // Process the received COG position and calculate control commands
    // assuming the control commands are stored in u[0] and u[1] for pan and tilt motors respectively
    double control_commands[2] = {/* Calculate the control commands based on the received COG position */};

    // Send the control commands to the 20sim wrapper/controller
    for (int i = 0; i < 2; i++)
    {
      controller_uPorts[i]->send(control_commands[i]);
    }

    // Receive the motor position from the 20sim wrapper/controller
    double motor_positions[2];
    for (int i = 0; i < 2; i++)
    {
      controller_yPorts[i]->receive(&motor_positions[i]);
    }

    RCLCPP_INFO(this->get_logger(), "Motor positions: Pan: %f, Tilt: %f", motor_positions[0], motor_positions[1]);

    // Call the 20sim wrapper/controller to calculate the next state
    controller_runnable->Calculate();
  }
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<LoopController>());
  rclcpp::shutdown();
  return 0;
}
