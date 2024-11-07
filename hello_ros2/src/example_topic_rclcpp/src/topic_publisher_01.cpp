#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>
class TopicPublisher01 : public rclcpp::Node
{
    public:
    TopicPublisher01(std::string name) : Node(name)   
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is%s!", name.c_str());
        command_publisher_=this->create_publisher<std_msgs::msg::String>("command",10);
        timer_=this->create_wall_timer(std::chrono::milliseconds(500),[this](){TopicPublisher01::timer_callback();});
    }
    private:
    void timer_callback(){
    std_msgs::msg::String message;
    message.data="hello world";
    RCLCPP_INFO(this->get_logger(),"Publishing : %s",message.data.c_str());
    command_publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};
int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicPublisher01>("rclcpp_node_3");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
