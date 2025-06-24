#include "rclcpp/rclcpp.hpp"
#include "buggy/msg/custom_msg.hpp"
#include "buggy/srv/custom_srv.hpp"
#include <iostream>

using std::placeholders::_1;

bool flag = false;
bool flag2 = false;

void callback(const buggy::msg::CustomMsg::SharedPtr msg)
{
  flag = msg->flag.data;
}

bool handle_service(const std::shared_ptr<buggy::srv::CustomSrv::Request> req,
                    std::shared_ptr<buggy::srv::CustomSrv::Response> res)
{
  flag2 = req->flag.data;
  res->result.data = flag2;
  return true;
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("sub");

  auto sub = node->create_subscription<buggy::msg::CustomMsg>(
    "/topic", 10, std::bind(callback, _1));

  auto srv = node->create_service<buggy::srv::CustomSrv>(
    "/turnon", handle_service);

  rclcpp::Rate rate(2);
  while (rclcpp::ok()) {
    if (flag && flag2) {
      std::cout << "You finished, congrats on 10 points\n";
    }
    rclcpp::spin_some(node);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}