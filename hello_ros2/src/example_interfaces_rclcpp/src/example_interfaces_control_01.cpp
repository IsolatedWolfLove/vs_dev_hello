#include "rclcpp/rclcpp.hpp"
#include "example_ros2_interfaces/msg/robot_status.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"
class ExampleInterfacesControl : public rclcpp::Node {
public:
    ExampleInterfacesControl(std::string name): Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", name.c_str());
        client_=this->create_client<example_ros2_interfaces::srv::MoveRobot>("move_robot");
        robot_status_subscriber_ = this->create_subscription<example_ros2_interfaces::msg::RobotStatus>("robot_status", 10, 										 std::bind(&ExampleInterfacesControl::robot_status_callback, this, std::placeholders::_1));
    }
    void move_robot(float distance)
    {
        RCLCPP_INFO(this->get_logger(), "Sending request to move robot by %f", distance);
        while(!client_->wait_for_service(std::chrono::seconds(1)))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
        }
        auto request=std::make_shared<example_ros2_interfaces::srv::MoveRobot::Request>();
        request->distance=distance;
        client_->async_send_request(request,std::bind(&ExampleInterfacesControl::result_callback, this, std::placeholders::_1));
        }
    private:
    rclcpp::Client<example_ros2_interfaces::srv::MoveRobot>::SharedPtr client_;
    rclcpp::Subscription<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_subscriber_;
    void result_callback(rclcpp::Client<example_ros2_interfaces::srv::MoveRobot>::SharedFuture result_future)
    {
        auto response=result_future.get();
        RCLCPP_INFO(this->get_logger(), "Result of move robot is %f", response->pose);
    }
    void robot_status_callback(const example_ros2_interfaces::msg::RobotStatus::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received robot status: %d, current_pose: %f", msg->status, msg->pose);
    }
};
int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ExampleInterfacesControl>("example_interfaces_control");
    node->move_robot(1.0);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
