// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from asdfr_interfaces:msg/Point2.idl
// generated code does not contain a copyright notice
#include "asdfr_interfaces/msg/detail/point2__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
asdfr_interfaces__msg__Point2__init(asdfr_interfaces__msg__Point2 * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  return true;
}

void
asdfr_interfaces__msg__Point2__fini(asdfr_interfaces__msg__Point2 * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
}

bool
asdfr_interfaces__msg__Point2__are_equal(const asdfr_interfaces__msg__Point2 * lhs, const asdfr_interfaces__msg__Point2 * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  return true;
}

bool
asdfr_interfaces__msg__Point2__copy(
  const asdfr_interfaces__msg__Point2 * input,
  asdfr_interfaces__msg__Point2 * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

asdfr_interfaces__msg__Point2 *
asdfr_interfaces__msg__Point2__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  asdfr_interfaces__msg__Point2 * msg = (asdfr_interfaces__msg__Point2 *)allocator.allocate(sizeof(asdfr_interfaces__msg__Point2), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(asdfr_interfaces__msg__Point2));
  bool success = asdfr_interfaces__msg__Point2__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
asdfr_interfaces__msg__Point2__destroy(asdfr_interfaces__msg__Point2 * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    asdfr_interfaces__msg__Point2__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
asdfr_interfaces__msg__Point2__Sequence__init(asdfr_interfaces__msg__Point2__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  asdfr_interfaces__msg__Point2 * data = NULL;

  if (size) {
    data = (asdfr_interfaces__msg__Point2 *)allocator.zero_allocate(size, sizeof(asdfr_interfaces__msg__Point2), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = asdfr_interfaces__msg__Point2__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        asdfr_interfaces__msg__Point2__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
asdfr_interfaces__msg__Point2__Sequence__fini(asdfr_interfaces__msg__Point2__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      asdfr_interfaces__msg__Point2__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

asdfr_interfaces__msg__Point2__Sequence *
asdfr_interfaces__msg__Point2__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  asdfr_interfaces__msg__Point2__Sequence * array = (asdfr_interfaces__msg__Point2__Sequence *)allocator.allocate(sizeof(asdfr_interfaces__msg__Point2__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = asdfr_interfaces__msg__Point2__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
asdfr_interfaces__msg__Point2__Sequence__destroy(asdfr_interfaces__msg__Point2__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    asdfr_interfaces__msg__Point2__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
asdfr_interfaces__msg__Point2__Sequence__are_equal(const asdfr_interfaces__msg__Point2__Sequence * lhs, const asdfr_interfaces__msg__Point2__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!asdfr_interfaces__msg__Point2__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
asdfr_interfaces__msg__Point2__Sequence__copy(
  const asdfr_interfaces__msg__Point2__Sequence * input,
  asdfr_interfaces__msg__Point2__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(asdfr_interfaces__msg__Point2);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    asdfr_interfaces__msg__Point2 * data =
      (asdfr_interfaces__msg__Point2 *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!asdfr_interfaces__msg__Point2__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          asdfr_interfaces__msg__Point2__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!asdfr_interfaces__msg__Point2__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
