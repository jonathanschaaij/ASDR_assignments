// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "asdfr_interfaces/msg/detail/point2__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace asdfr_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Point2_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) asdfr_interfaces::msg::Point2(_init);
}

void Point2_fini_function(void * message_memory)
{
  auto typed_message = static_cast<asdfr_interfaces::msg::Point2 *>(message_memory);
  typed_message->~Point2();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Point2_message_member_array[2] = {
  {
    "x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(asdfr_interfaces::msg::Point2, x),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(asdfr_interfaces::msg::Point2, y),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Point2_message_members = {
  "asdfr_interfaces::msg",  // message namespace
  "Point2",  // message name
  2,  // number of fields
  sizeof(asdfr_interfaces::msg::Point2),
  Point2_message_member_array,  // message members
  Point2_init_function,  // function to initialize message memory (memory has to be allocated)
  Point2_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Point2_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Point2_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace asdfr_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<asdfr_interfaces::msg::Point2>()
{
  return &::asdfr_interfaces::msg::rosidl_typesupport_introspection_cpp::Point2_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, asdfr_interfaces, msg, Point2)() {
  return &::asdfr_interfaces::msg::rosidl_typesupport_introspection_cpp::Point2_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
