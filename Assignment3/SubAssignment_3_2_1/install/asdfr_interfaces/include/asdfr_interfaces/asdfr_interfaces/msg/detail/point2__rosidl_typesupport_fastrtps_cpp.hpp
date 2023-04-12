// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice

#ifndef ASDFR_INTERFACES__MSG__DETAIL__POINT2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ASDFR_INTERFACES__MSG__DETAIL__POINT2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "asdfr_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "asdfr_interfaces/msg/detail/point2__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace asdfr_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_asdfr_interfaces
cdr_serialize(
  const asdfr_interfaces::msg::Point2 & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_asdfr_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  asdfr_interfaces::msg::Point2 & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_asdfr_interfaces
get_serialized_size(
  const asdfr_interfaces::msg::Point2 & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_asdfr_interfaces
max_serialized_size_Point2(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace asdfr_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_asdfr_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, asdfr_interfaces, msg, Point2)();

#ifdef __cplusplus
}
#endif

#endif  // ASDFR_INTERFACES__MSG__DETAIL__POINT2__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
