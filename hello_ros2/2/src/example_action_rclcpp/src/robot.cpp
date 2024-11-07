#include "example_action_rclcpp/robot.h"
float Robot::move_step(){
    int direct=move_distance_/fabs(move_distance_);
    float step = direct * fabs(target_pose_ - current_pose_) * 0.1;
    current_pose_+=step;
    std::cout<<"moving distance: "<<step<<" current_pose: "<<current_pose_<<" target_pose: "<<target_pose_<<std::endl;
    return current_pose_;
}
bool Robot::set_goal(float distance){
    move_distance_=distance;
    target_pose_+=distance;
    if (close_goal()) {
        status_=MoveRobot::Feedback::STATUS_STOP;
        return false;
    }
    status_=MoveRobot::Feedback::STATUS_MOVING;
    return true;
}
float Robot::get_current_pose(){
    return current_pose_;
}
int Robot::get_status(){
    return status_;
}
bool Robot::close_goal(){
    if (std::fabs(target_pose_ - current_pose_) < 0.01) {
        return true;
    }
    return false;
}
void Robot::stop_move(){
    status_=MoveRobot::Feedback::STATUS_STOP;
}
