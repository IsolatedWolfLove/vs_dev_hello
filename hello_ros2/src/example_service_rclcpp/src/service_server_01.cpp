#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
class ServiceServer01 : public rclcpp::Node
{
public:
    ServiceServer01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "Hello my name is %s", name.c_str());
        add_int_service_=this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints",std::bind(&ServiceServer01::handle_add_two_ints, this, std::placeholders::_1, std::placeholders::_2));

    }
    private:
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr add_int_service_;
    void handle_add_two_ints(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request, std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
    RCLCPP_INFO(this->get_logger(),"commit a:%ld b: %ld ",request->a,request->b);
        response->sum=request->a+request->b;
    }};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServiceServer01>("service_server_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
