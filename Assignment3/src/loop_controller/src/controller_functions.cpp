#include <stdexcept>

#include "controller_functions.h"

void ReadConvert(const double *src, double *dst)
{
  printf("Readconvert called");

  // Example implementation!
  static double lastKnownGoodValue = 0;
  /* We assume that src is a 3 element double array, which has:
   * src[0] = temperature reading in degrees Fahrenheit (scaling)
   * -> We want the output in degrees Celcius
   * src[1] = some measurement with unreliable communication; once
   * in a while a (faulty) 0 is received; this should be
   * filtered and the previous value should be passed (filtering)
   * src[2] = some good measurement which does not need
   * scaling neither filtering
   */
  dst[0] = (src[0] - 32.0) / 1.8; // scaling
  if (src[1] != 0)                // filtering
  {
    dst[1] = src[1];
    lastKnownGoodValue = src[1];
  }
  else
  {
    dst[1] = lastKnownGoodValue;
  }
  dst[2] = src[2]; // passing
}
void WriteConvert(const double *src, double *dst)
{
  printf("Writeconvert called");
}
