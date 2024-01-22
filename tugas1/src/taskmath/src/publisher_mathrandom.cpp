#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("mathcalculations", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    
    std::random_device rd;
    std::mt19937 generator(rd());
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    char operators[5] = {'+', '-', '*', '/', '%'};
    message.data = std::to_string(random_number()) + " " + operators[random_operator()] + " " + std::to_string(random_number()) + " " + operators[random_operator()] + " " + std::to_string(random_number());
    RCLCPP_INFO(this->get_logger(), "%s", message.data.c_str());
    publisher_->publish(message);
  }

  int random_number()
  {
    std::uniform_int_distribution<int> distribution(1, 10000);
    return distribution(generator);
  }

  int random_operator()
  {
    std::uniform_int_distribution<int> distribution(0, 4);
    return distribution(generator);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  std::mt19937 generator;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
