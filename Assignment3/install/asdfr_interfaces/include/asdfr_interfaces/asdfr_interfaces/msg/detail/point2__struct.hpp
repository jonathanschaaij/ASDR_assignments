// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice

#ifndef ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_HPP_
#define ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__asdfr_interfaces__msg__Point2 __attribute__((deprecated))
#else
# define DEPRECATED__asdfr_interfaces__msg__Point2 __declspec(deprecated)
#endif

namespace asdfr_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Point2_
{
  using Type = Point2_<ContainerAllocator>;

  explicit Point2_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->y = 0.0;
    }
  }

  explicit Point2_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->x = 0.0;
      this->y = 0.0;
    }
  }

  // field types and members
  using _x_type =
    double;
  _x_type x;
  using _y_type =
    double;
  _y_type y;

  // setters for named parameter idiom
  Type & set__x(
    const double & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const double & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    asdfr_interfaces::msg::Point2_<ContainerAllocator> *;
  using ConstRawPtr =
    const asdfr_interfaces::msg::Point2_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      asdfr_interfaces::msg::Point2_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      asdfr_interfaces::msg::Point2_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__asdfr_interfaces__msg__Point2
    std::shared_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__asdfr_interfaces__msg__Point2
    std::shared_ptr<asdfr_interfaces::msg::Point2_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Point2_ & other) const
  {
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const Point2_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Point2_

// alias to use template instance with default allocator
using Point2 =
  asdfr_interfaces::msg::Point2_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace asdfr_interfaces

#endif  // ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_HPP_
