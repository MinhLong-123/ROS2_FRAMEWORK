#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;
class TurtlesimSubscriber : public rclcpp::Node
{
    public:
        TurtlesimSubscriber() : Node("turtlesim_subscriber")
        {
            subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
                "turtle1/cmd_vel", 10, std::bind(&TurtlesimSubscriber::subscribe_message, this, _1));

        }
    private:
        void subscribe_message(const geometry_msgs::msg::Twist& msg) const
        {
            RCLCPP_INFO(this->get_logger(), "Received velocity - Linear velocity: %f, Angular velocity: %f", msg.linear.x, msg.angular.z);
        }
        rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtlesimSubscriber>());
    rclcpp::shutdown();
    return 0;
}