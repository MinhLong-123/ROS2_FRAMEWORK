#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
class MinimalPublisher : public rclcpp::Node  // Create a node class that inherits from rclcpp::Node
{
    public:
        // Constructor for the MinimalPublisher class
        // This constructor initializes the node with the name "minimal_publisher"
        MinimalPublisher() : Node("minimal_publisher"), count_(0)
        {
            // Create a publisher for the topic "simple_topic" with the String message type. "this" in the code is referring to the node itself.
            publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);  
            // Create a timer that calls the timer_callback function every 500 milliseconds
            // The timer is created using the create_wall_timer method, which takes a duration and a callback function
            // The duration is specified using the std::chrono::milliseconds type
            // The callback function is specified using std::bind, which binds the timer_callback function to the current instance of the class
            timer_ = this->create_wall_timer(
                100ms, std::bind(&MinimalPublisher::timer_callback, this));
        }
    private:
        void timer_callback()
        {
            // Create a message of type String and set its data to "Hello, world!" followed by the current count
            auto message = std_msgs::msg::String();
            message.data = "Hello, world! " + std::to_string(count_++);
            RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
            // Publish the message to the topic "simple_topic"
            publisher_->publish(message);
        }
        // Declare a publisher for the topic "simple_topic" with the String message type
        // The publisher is a shared pointer, which allows multiple parts of the code to share ownership of the publisher object
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        // Declare a timer that will call the timer_callback function at regular intervals
        // The timer is a shared pointer, which allows multiple parts of the code to share ownership of the timer object
        rclcpp::TimerBase::SharedPtr timer_;
        // Declare a counter variable to keep track of the number of messages published
        // The counter is of type size_t, which is an unsigned integer type
        size_t count_;
};
int main(int argc, char * argv[])
{
    // Initialize the ROS 2 C++ client library
    // The rclcpp::init function initializes the library and prepares it for use
    rclcpp::init(argc, argv);
    // Create a shared pointer to an instance of the MinimalPublisher class and start processing data from the node, including the timer
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    // Shutdown the ROS 2 C++ client library
    rclcpp::shutdown();
    return 0;
}


