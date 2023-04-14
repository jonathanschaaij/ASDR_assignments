#include <stdio.h>
#include <unistd.h>
#include <iterator>
#include <signal.h>
#include <vector>
#include <sys/syscall.h>
#include <cmath>
#include <assert.h>

#include "framework/multiCommClass.h"
#include "framework/runnableClass.h"
#include "framework/superThread.h"
#include "framework/icoCommClass.h"
#include "ControllerPan/ControllerPan.h"
// #include <Your 20-sim-code-generated h-file?> Don't forget to compile the cpp file by adding it to CMakeLists.txt

volatile bool exitbool = false;

void myReadConvert(const double *src, double *dst)
{
    // [ P1_ENC, P1_IN_1, P1_IN2, P2_ENC, P2_IN_1, P2_IN2, P3_ENC, P3_IN_1, P3_IN2, P4_ENC, P4_IN_1, P4_IN2]
    // Tilt = 2000 per rev  1:1 ratio  index 0
    // Pan = 1250 per rev   4:1 ratio  index 3

    // Convert Tilt encoder to angle, where center is 0.
    if (src[0] > 8191)
    {
        dst[0] = round((2 * M_PI * (src[0] - 16384) / 2000) * 100) / 100;
    }
    else
    {
        dst[0] = round((2 * M_PI * src[0] / 2000) * 100) / 100;
    }

    // Convert Pan encoder to angle, where center is 0.
    if (src[3] > 8191)
    {
        dst[3] = round((2 * M_PI * (src[3] - 16384) / (1250)) * 100) / 100;
    }
    else
    {
        dst[3] = round((2 * M_PI * src[3] / (1250)) * 100) / 100;
    }
}

void myWriteConvert(const double *src, double *dst)
{
    // [P1_PWM, P1_OUT_1, P2_PWM, P2_OUT_1, P3_PWM, P3_OUT_1, P4_PWM, P4_OUT_1]
    // Convert percentile from -1 1 range to -2047 2047 range
    dst[0] = round(src[0] * 2047); // Round to nearest integer
    dst[2] = round(src[2] * 2047); // Round to nearest integer
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

    int xddpSetpoint_sendParam[] = {0};                                // input setpoint to the first place of the U of the controller
    int icomcomm_sendParam[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // input of the icomcomm class to the FPGA
    int icomcomm_recvParam[] = {0, 1, 2, 3, 4, 5, 6, 7};               // output of the icomcomm class from the FPGA
    IcoComm *icoComm;
    icoComm = new IcoComm(icomcomm_sendParam, icomcomm_recvParam);
    icoComm->setReadConvertFcn(&myReadConvert);
    icoComm->setWriteConvertFcn(&myWriteConvert);
    frameworkComm *controller_sendPorts[] = {
        new XDDPComm(10, -1, 1, xddpSetpoint_sendParam),
        icoComm};
    frameworkComm *controller_recvPorts[] = {
        icoComm};

    ControllerPan *controller_class = new ControllerPan;
    runnable *controller_runnable = new wrapper<ControllerPan>(
        controller_class, controller_sendPorts, controller_recvPorts, 2, 1);
    controller_runnable->setSize(2, 1);

    // INIT XENOTRHEAD FOR CONTROLLER
    xenoThread controllerClass(controller_runnable);
    controllerClass.init(1000000, 99, 0);
    controllerClass.enableLogging(true, 26);

    // START THREADS
    controllerClass.start("ControllerPan");

    // WAIT FOR CNTRL-C
    timespec t = {.tv_sec = 0, .tv_nsec = 100000000};

    while (!exitbool)
    {
        // Let the threads do the real work
        nanosleep(&t, NULL);
        // Wait for Ctrl-C to exit
    }

    printf("Ctrl-C was pressed: Stopping gracefully...\n");

    // CLEANUP HERE
    controllerClass.stopThread();
    controller_runnable->~runnable();

    return 0;
}
