#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
class ServiceClient01 : public rclcpp::Node
{
public:
    ServiceClient01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", name.c_str());
        client_=this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        
    }
    void send_request(int a, int b)
    {
        RCLCPP_INFO(this->get_logger(), "Sending request to add %d and %d", a, b);
        while(!client_->wait_for_service(std::chrono::seconds(1)))
        {
            if(!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
        } 
        auto request=std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a=a;
        request->b=b;
        client_->async_send_request(request,std::bind(&ServiceClient01::result_callback, this, std::placeholders::_1));
        }
    private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;
    void result_callback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture result_future)
    {
        auto result=result_future.get();
        RCLCPP_INFO(this->get_logger(), "Result of add two int is %ld", result->sum);
    }
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServiceClient01>("service_client_01");
    node->send_request(5,6);

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
