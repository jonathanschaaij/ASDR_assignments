// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice

#ifndef ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_H_
#define ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Point2 in the package asdfr_interfaces.
typedef struct asdfr_interfaces__msg__Point2
{
  double x;
  double y;
} asdfr_interfaces__msg__Point2;

// Struct for a sequence of asdfr_interfaces__msg__Point2.
typedef struct asdfr_interfaces__msg__Point2__Sequence
{
  asdfr_interfaces__msg__Point2 * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} asdfr_interfaces__msg__Point2__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ASDFR_INTERFACES__MSG__DETAIL__POINT2__STRUCT_H_
