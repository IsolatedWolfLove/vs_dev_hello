#include "example_ros2_interfaces/msg/robot_status.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"
#include "rclcpp/rclcpp.hpp"

class Robot {
public:
    Robot() = default;
    ~Robot() = default;
    float move_distance(float distance)
    {
        status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_MOVING;
        target_pose_ += distance;
        while (std::fabs(target_pose_ - current_pose_) > 0.01) {
            float step = distance / fabs(distance) * fabs(target_pose_ - current_pose_) * 0.1;
            current_pose_ += step;
            std::cout << "moving distance: " << step << " current_pose: " << current_pose_ << " target_pose: " << target_pose_ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
        return current_pose_;
    }
    float get_current_pose()
    {
        return current_pose_;
    }
int get_status()
    {
        return status_;
    }
private:
    float current_pose_ = 0.0;
    float target_pose_ = 0.0;
    int status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
};
class ExampleInterfacesRobot : public rclcpp::Node {
public:
    ExampleInterfacesRobot(std::string name)
        : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", name.c_str());
        move_robot_server_ = this->create_service<example_ros2_interfaces::srv::MoveRobot>("move_robot", std::bind(&ExampleInterfacesRobot::handle_move_robot, this, std::placeholders::_1, std::placeholders::_2));
        robot_status_publisher_ = this->create_publisher<example_ros2_interfaces::msg::RobotStatus>("robot_status", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&ExampleInterfacesRobot::timer_callback, this));
    }

private:
    Robot robot;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Service<example_ros2_interfaces::srv::MoveRobot>::SharedPtr move_robot_server_;
    rclcpp::Publisher<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_publisher_;
    void timer_callback() { 
        example_ros2_interfaces::msg::RobotStatus message;
message.status = robot.get_status();
message.pose = robot.get_current_pose();
RCLCPP_INFO(this->get_logger(), "robot status: %d, current_pose: %f", message.status, message.pose);
robot_status_publisher_->publish(message);
    }
    void handle_move_robot(const std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Request> request, const std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Response> response) {
    RCLCPP_INFO(this->get_logger(), "Received request to move robot by %f", request->distance);
    robot.move_distance(request->distance);
    response->pose = robot.get_current_pose();
    }
};
int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ExampleInterfacesRobot>("example_interfaces_robot");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
