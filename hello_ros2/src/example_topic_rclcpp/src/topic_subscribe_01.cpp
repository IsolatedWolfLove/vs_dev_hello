#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
class TopicSubscriber01 : public rclcpp::Node
{
public:
    TopicSubscriber01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", name.c_str());
        commend_subscribe_=this->create_subscription<std_msgs::msg::String>("command",10,std::bind(&TopicSubscriber01::topic_callback, this, std::placeholders::_1));
    }
    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr commend_subscribe_;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed=0.0;
        if(msg->data=="hello world"){
            speed=0.2;
        }
        RCLCPP_INFO(this->get_logger(), "I heard: [%s] ,send speed %f", msg->data.c_str(),speed);    
    }
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicSubscriber01>("topic_subscriber_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
