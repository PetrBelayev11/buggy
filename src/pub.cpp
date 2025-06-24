#include "rclcpp/rclcpp.hpp"
#include "buggy/msg/custom_msg.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("pub");

  auto publisher = node->create_publisher<buggy::msg::CustomMsg>("/topic", 10);

  rclcpp::Rate loop_rate(2);

  while (rclcpp::ok()) {
    buggy::msg::CustomMsg msg;
    msg.name.data = "buggy_msg";
    msg.flag.data = true;
    publisher->publish(msg);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}