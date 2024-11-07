#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"
class ActionController01 : public rclcpp::Node {
public:
    using MoveRobot = robot_control_interfaces::action::MoveRobot;
    using GoalHandleMoveRobot = rclcpp_action::ServerGoalHandle<MoveRobot>;
    explicit ActionController01(const std::string& node_name, const rclcpp::NodeOptions& node_options = rclcpp::NodeOptions())
        : Node(node_name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", node_name.c_str());
        this->client_ = this->create_client<MoveRobot>("move_robot");
        this->timer_ = this->create_wall_timer(std::chrono::milliseconds(100), std::bind(&ActionController01::send_goal, this));
    }
    void send_goal()
    {
        using namespace std::placeholders;
        this->timer_->cancel();
        if (!this->client->wait_for_service(std::chrono::seconds(1)))
            RCLCPP_ERROR(this->get_logger(), "Action srever not available, while waiting for service");
        rclcpp::shutdown();
        return;
    }
   MoveRobot::Goal goal_msg = MoveRobot::Goal();
    goal_msg.distance = 10;
    RCLCPP_INFO(this->get_logger(), "Sending goal request with distance %f", goal_msg.distance);
    auto send_goal_options = rclcpp_action::Client<MoveRobot>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&ActionController01::goal_response_callback, this, _1);
    send_goal_options.feedback_callback = std::bind(&ActionController01::feedback_callback, this, _1);
    send_goal_options.result_callback = std::bind(&ActionController01::result_callback, this, _1);
    this->client_ptr->async_send_goal(goal_msg, send_goal_options);

private:
    rclcpp_action::Client<MoveRobot>::SharedPtr client_ptr;
    rclcpp::TimerBase::SharedPtr timer_;
    void goal_response_callback(GoalHandleMoveRobot::SharedPtr goal_handle)
    {
        if (!goal_handle) {
            RCLCPP_ERROR(this->get_logger(), "Goal rejected");
        } else {
            RCLCPP_INFO(this->get_logger(), "Goal accepted,waiting for result");
        }
    }
    void feedback_callback(GoalHandleMoveRobot::SharedPtr, const std::shared_ptr<const MoveRobot::Feedback>& feedback)
    {
        RCLCPP_INFO(this->get_logger(), "Received feedback with pose %f and status %d", feedback->pose, feedback->status);
    }
    void result_callback(const GoalHandleMoveRobot::WrappedResult& result){
        switch (result.code) {
            case rclcpp_action::ResultCode::SUCCEEDED:
            break;
            case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal aborted");
            return;
            case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal canceled");
            return;
            default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            return;
        }
            RCLCPP_INFO(this->get_logger(),"result: %f", result.result->pose);
            
    }

};
int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ActionController01>("action_controller_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
