#include <memory>
#include <iomanip>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("subscriber")
  {
    subscription1_ = this->create_subscription<std_msgs::msg::String>(
      "info1", 10, std::bind(&MinimalSubscriber::topic_callback1, this, _1));

    subscription2_ = this->create_subscription<std_msgs::msg::String>(
      "info2", 10, std::bind(&MinimalSubscriber::topic_callback2, this, _1));
  }

private:
  bool latest_pub1_state = false;
  bool latest_pub2_state = false;


private:
  void topic_callback1(const std_msgs::msg::String::SharedPtr msg)
  {
    if (msg->data[msg->data.size() - 4] == 't') {
      latest_pub1_state = true;
    } else {
      latest_pub1_state = false;
    }

    check_publisher_states();
  }

  void topic_callback2(const std_msgs::msg::String::SharedPtr msg)
  {
    if (msg->data[msg->data.size() - 4] == 't') {
      latest_pub2_state = true;
    } else {
      latest_pub2_state = false;
    }

    check_publisher_states();
  }

  void check_publisher_states()
  {
    rclcpp::Time now = this->get_clock()->now();
    int seconds = now.seconds();
    std::stringstream timestamp_stream;
    timestamp_stream << "pub1 (detik-" << seconds << "." << std::setfill('0') << std::setw(2) << (int)(now.nanoseconds() / 1000000) << ") = " << (latest_pub1_state ? "true" : "false") << " | pub2 (detik-" << seconds << "." << std::setfill('0') << std::setw(2) << (int)(now.nanoseconds() / 1000000) << ") = " << (latest_pub2_state ? "true" : "false");
    std::string timestamp = timestamp_stream.str();

    if (latest_pub1_state && latest_pub2_state) {
      RCLCPP_INFO(this->get_logger(), "%s -> \"Sudah siap nih, gass min!\"", timestamp.c_str());
    } else {
      RCLCPP_INFO(this->get_logger(), "%s -> \"Tunggu dulu, kami belum ready!\"", timestamp.c_str());
    }
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription1_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription2_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}