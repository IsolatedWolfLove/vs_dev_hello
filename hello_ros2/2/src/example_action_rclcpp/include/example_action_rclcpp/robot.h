#ifndef EXAMPLE_ACTION_RCLCPP_RBOBT_H_
#define EXAMPLE_ACTION_RCLCPP_RBOBT_H_
#include "rclcpp/rclcpp.hpp"
#include "robot_control_interfaces/action/move_robot.hpp"
#include <atomic>
class Robot {
public:
    Robot() = default;
    ~Robot() = default;
    using MoveRobot=robot_control_interfaces::action::MoveRobot;
    float move_step();
    bool set_goal(float distance);
    float get_current_pose();
    int get_status();
    bool close_goal();
    void stop_move();
private:
float current_pose_ = 0.0;
float target_pose_ = 0.0;
int status_ = MoveRobot::Feedback::STATUS_STOP;
float move_distance_ = 0.0;
std::atomic<bool> cancel_goal_{false};
};
#endif // EXAMPLE_ACTION_RCLCPP_RBOBT_H_
