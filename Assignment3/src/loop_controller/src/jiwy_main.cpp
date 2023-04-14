#include <stdio.h>
#include <unistd.h>
#include <iterator>
#include <signal.h>
#include <vector>
#include <sys/syscall.h>

#include "framework/multiCommClass.h"
#include "framework/runnableClass.h"
#include "framework/superThread.h"
#include "framework/icoCommClass.h"
#include "ControllerPan.h"
// #include <Your 20-sim-code-generated h-file?> Don't forget to compile the cpp file by adding it to CMakeLists.txt

volatile bool exitbool = false;

#define PI 3.14159265358979323846 /* pi */

void myReadConvert(const double *src, double *dst)
{
    printf("ReadConv:");
    printf("0: %d\n", src[0]);
    printf("1: %d\n", src[1]);
    printf("2: %d\n", src[2]);
    printf("3: %d\n", src[3]);
    // Pan = 1250 per rev   4:1 ratio ICOboard P2  index 3
    // Tilt = 2000 per rev  1:1 ratio ICOboard P1  index 0
    // Size = 12
    // [ P1_ENC, P1_IN_1, P1_IN2, P2_ENC, P2_IN_1, P2_IN2, P3_ENC, P3_IN_1, P3_IN2, P4_ENC, P4_IN_1, P4_IN2]
    // Convert encoder to angle, where center is 0.
    if (src[3] > 7500)
    {
        dst[3] = 2 * PI * (src[3] - 16384) / 1250;
    }
    else
    {
        dst[3] = 2 * PI * (src[3]) / 1250;
    }
    /*
    if (src[0] > 7500) {
        dst[0] = 2*PI*(src[0] - 16384)/2000;
    }
    else {
        dst[0] = 2*PI*(src[0])/2000;
    }
    */
}
// POSITIVE PAN SHOULD MAKE SYSTEM LOOK TO THE RIGHT OR UP
void myWriteConvert(const double *src, double *dst)
{
    printf("WriteConv:");
    printf("0: %d\n", src[0]);
    printf("1: %d\n", src[1]);
    printf("2: %d\n", src[2]);
    printf("3: %d\n", src[3]);
    // Size = 8
    //[P1_PWM, P1_OUT_1, P2_PWM, P2_OUT_1, P3_PWM, P3_OUT_1, P4_PWM, P4_OUT_1 ]
    //  Convert percentile from -1 1 range to -2047 2047 range
    // dst[0] = src[0]*2047;
    dst[2] = src[2] * 2047;
}

void exit_handler(int s)
{
    printf("Caught signal %d\n", s);
    exitbool = true;
}

int main()
{
    // CREATE CNTRL-C HANDLER
    signal(SIGINT, exit_handler);

    printf("Press Ctrl-C to stop program\n");
    // Note: this will
    // not kill the program; just jump out of the wait loop. Hence,
    // you can still do proper clean-up. You are free to alter the
    // way of determining when to stop (e.g., run for a fixed time).

    // CONFIGURE, CREATE AND START THREADS HERE
    // CREATE PARAM AND WRAPPER FOR CONTROLLER
    // IDDP is real-time
    // XDDP is not real-time

    // This code is mostly from Bram Meijer's work
    // need to input one setpoint and the other value is the encoder value and y arameters

    int xddpSetpoint_uParam[] = {0};                                         // input setpoint to the first place of the U of the controller
    int icomcomm_uParam[] = {1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // input of the icomcomm class to the FPGA
    int icomcomm_yParam[] = {0, -1, -1, -1, -1, -1, -1, -1};                 // output of the icomcomm class from the FPGA
    icoComm = new IcoComm(icomcomm_uParam, icomcomm_yParam);
    // to use the Read and Write convert the following to lines can be uncommented but these are not tested.
    // icoComm.SetReadConvertFcn(&MyReadConvert);
    // icoComm.SetWriteConvertFcn(&MyReadConvert);
    frameworkComm *controller_uPorts[] = {
        new XDDPComm(10, -1, 1, xddpSetpoint_uParam),
        icoComm};
    frameworkComm *controller_yPorts[] = {
        icoComm};

    ControllerPan *controller_class = new ControllerPan;
    runnable *controller_runnable = new wrapper<ControllerPan>(
        controller_class, controller_uPorts, controller_yPorts, 2, 1);
    controller_runnable->setSize(2, 1);

    // INIT XENOTRHEAD FOR CONTROLLER
    xenoThread controllerClass(controller_runnable);
    controllerClass.init(1000000, 99, 0);
    // controllerClass.enableLogging(true, 26);

    // START THREADS
    controllerClass.start("ControllerPan");

    // WAIT FOR CNTRL-C
    timespec t = {.tv_sec = 0, .tv_nsec = 100000000}; // 1/10 second

    while (!exitbool)
    {
        // Let the threads do the real work
        nanosleep(&t, NULL);
        // Wait for Ctrl-C to exit
    }
    printf("Ctrl-C was pressed: Stopping gracefully...\n");

    // CLEANUP HERE
    controllerClass.stopThread();
    // controller_runnable->~xenoThread();
    controller_runnable->~runnable();
    return 0;
}