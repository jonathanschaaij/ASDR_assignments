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
#include "ControllerPan/ControllerPan.h"
// #include <Your 20-sim-code-generated h-file?> Don't forget to compile the cpp file by adding it to CMakeLists.txt

volatile bool exitbool = false;

void exit_handler(int s)
{
    printf("Caught signal %d\n", s);
    exitbool = true;
}

int main()
{
    //CREATE CNTRL-C HANDLER
    signal(SIGINT, exit_handler);

    printf("Press Ctrl-C to stop program\n"); // Note: this will 
        // not kill the program; just jump out of the wait loop. Hence,
        // you can still do proper clean-up. You are free to alter the
        // way of determining when to stop (e.g., run for a fixed time).

    // CONFIGURE, CREATE AND START THREADS HERE
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

    xenoThread controllerClass(controller_runnable);
    controllerClass.init(1000000, 99, 0);

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

    //CLEANUP HERE
    controllerClass.stopThread();
    delete controller_runnable;

    return 0;
}