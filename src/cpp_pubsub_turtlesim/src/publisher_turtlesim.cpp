#include <chrono>
#include <memory>
#include <string>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class TurtlesimPublisher : public rclcpp::Node
{
    public:
        TurtlesimPublisher() : Node("turtlesim_publisher")
        {
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel",10);
            i = 0.0;
            timer_ = this->create_wall_timer(500ms, std::bind(&TurtlesimPublisher::publish_velocity, this));
        }
    private:
        void publish_velocity()
        {
            auto message = geometry_msgs::msg::Twist();
            message.linear.x = 4.0;
            message.angular.z = 2.0 + i;
            RCLCPP_INFO(this->get_logger(), "Sending velocity - Linear velocty: %f, Angular velocity: %f", message.linear.x, message.angular.z);
            publisher_->publish(message);
            i += 0.1;
        }
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        float i;
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TurtlesimPublisher>());
    rclcpp::shutdown();
    return 0;
}
