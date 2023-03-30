// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice

#ifndef ASDFR_INTERFACES__MSG__DETAIL__POINT2__BUILDER_HPP_
#define ASDFR_INTERFACES__MSG__DETAIL__POINT2__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "asdfr_interfaces/msg/detail/point2__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace asdfr_interfaces
{

namespace msg
{

namespace builder
{

class Init_Point2_y
{
public:
  explicit Init_Point2_y(::asdfr_interfaces::msg::Point2 & msg)
  : msg_(msg)
  {}
  ::asdfr_interfaces::msg::Point2 y(::asdfr_interfaces::msg::Point2::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::asdfr_interfaces::msg::Point2 msg_;
};

class Init_Point2_x
{
public:
  Init_Point2_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Point2_y x(::asdfr_interfaces::msg::Point2::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Point2_y(msg_);
  }

private:
  ::asdfr_interfaces::msg::Point2 msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::asdfr_interfaces::msg::Point2>()
{
  return asdfr_interfaces::msg::builder::Init_Point2_x();
}

}  // namespace asdfr_interfaces

#endif  // ASDFR_INTERFACES__MSG__DETAIL__POINT2__BUILDER_HPP_
