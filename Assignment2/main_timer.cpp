#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <signal.h>
#include <fstream>

bool doStuff = false;

void signalHandler(int signum) {
    doStuff = true;
    // std::cout << "Interrupt signal " << std::endl;
}

void sum_from_1_to_n(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
}

void *empty_thread_function(void *arg)
{
    // Create the timer
    timer_t timer_id;
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;
    sev.sigev_value.sival_ptr = &timer_id;
    timer_create(CLOCK_REALTIME, &sev, &timer_id);

    // Set the timer to expire every 1ms
    struct itimerspec its;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 1000000; // 1ms
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 1000000; // 1ms
    timer_settime(timer_id, 0, &its, NULL);

    // Wait for the timer to expire using sigwait()
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);

    // Signal handler to prevent termination
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);



    // Set up the loop to track the time of each loop
	int count = 1000;
    struct timespec time[count + 1];
    clock_gettime(CLOCK_MONOTONIC, &time[0]);
    
    std::cout << "Before the loop" << std::endl;
    size_t i = 0;
    while (i < count)
    {
        int sig;
        if (doStuff) {
            doStuff = false;
            sum_from_1_to_n(1000000);
            clock_gettime(CLOCK_MONOTONIC, &time[i + 1]);
            i ++;
        }
    }

    printf("After the loop\n");

    std::ofstream myfile;            // create output file stream
    myfile.open("time_clock_" + std::to_string(time[0].tv_sec) + ".csv"); // open file for writing

    myfile << "TIME";
    // write array elements to file
    for (int i = 0; i < count+1; i++)
    {
        float t = (time[i].tv_sec + time[i].tv_nsec / 1000000000.0);
        myfile << t;
        myfile << std::endl; // Add new line to the last element
    }

    myfile.close(); // close file

    float elapsed_time = (time[count+1].tv_sec - time[0].tv_sec) + (time[count +1].tv_nsec - time[0].tv_nsec) / 1000000000.0;
    return 0;
}

int main()
{
    pthread_t thread_id;
    double elapsed_time;
    int status;

    printf("Starting Thread\n");
    status = pthread_create(&thread_id, NULL, empty_thread_function, NULL);
    status = pthread_join(thread_id, NULL);
    printf("Thread has ended\n");

    return 0;
}
