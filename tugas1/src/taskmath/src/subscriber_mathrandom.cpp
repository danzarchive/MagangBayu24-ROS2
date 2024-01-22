#include <memory>
#include <vector>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

float evaluate(float num1, char op, float num2)
{
  if (op == '+') {
    return num1 + num2;
  } else if (op == '-') {
    return num1 - num2;
  } else if (op == '*') {
    return num1 * num2;
  } else if (op == '/') {
    return num1 / num2;
  } else if (op == '%') {
    return float(int(num1) % int(num2));
  }
  return -1;
}

std::string calculate_expression(const std::string& expression)
{
  int result;
  int limit = 0;
  std::vector<int> numbers;
  std::vector<char> operators;

  for (size_t i = 0; i < expression.size(); i++) {
    if (expression[i] == ' ' || i == expression.size() - 1) {
      numbers.push_back(std::stoi(expression.substr(limit, i - limit + 1)));

      if (i != expression.size() - 1) {
        operators.push_back(expression[i + 1]);
      }

      i += 2;
      limit = i;
    }
  }

  if (operators[0] == '*' || operators[0] == '/' || operators[0] == '%')
  {
    result = int(evaluate(evaluate(float(numbers[0]), operators[0], float(numbers[1])), operators[1], float(numbers[2])));
  }
  else
  {
    result = int(evaluate(float(numbers[0]), operators[0], evaluate(float(numbers[1]), operators[1], float(numbers[2]))));
  }

  return std::to_string(result);
}

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "mathcalculations", 10, std::bind(&MinimalSubscriber::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
  {
    std::string expression = msg->data.c_str();
    std::string result = calculate_expression(expression);
    RCLCPP_INFO(this->get_logger(), expression + " = " + result);
  }

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}