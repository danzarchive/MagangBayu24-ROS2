#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class MyPublisher1 : public rclcpp::Node
{
private:
  bool state = false;
  std::chrono::seconds interval{1};
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  size_t count_{2};

  void timer_callback()
  {
    auto message = std::make_unique<std_msgs::msg::String>();
    message->data = "publisher-1-(" + std::to_string(count_) + " sec) → ";
    count_ += 1;
    if (state) {
      message->data += "false";
      state = false;
    } else {
      message->data += "true";
      state = true;
    }
    RCLCPP_INFO(this->get_logger(), "%s", message->data.c_str());
    publisher_->publish(std::move(message));
  }

public:
  MyPublisher1()
  : Node("my_publisher"), count_{0}
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("info1", 10);
    timer_ = this->create_wall_timer(interval, std::bind(&MyPublisher1::timer_callback, this));
  }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyPublisher1>());
  rclcpp::shutdown();
  return 0;
}