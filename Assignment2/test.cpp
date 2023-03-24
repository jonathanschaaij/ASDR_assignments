#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>


void sum_from_1_to_n(int n)
{
    std::cout << 6 << std::endl;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
}

void* timed_code(void* arg)
{
	std::cout << 1 << std::endl;

    struct sigevent sev;
    timer_t timerid;
    struct itimerspec its;
    struct timespec timeout;
    sigset_t waitset;

	std::cout << 2 << std::endl;

	timeout.tv_nsec = 1000000;  /* Number of nanoseconds to wait */
    // Set up the signal handler
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &timerid;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

	std::cout << 3 << std::endl;
    // Set up the timer
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 1000000; // 1ms
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 1000000; // 1ms
    timer_settime(timerid, 0, &its, NULL);

	std::cout << 4 << std::endl;
    int n = 1000000;
    for (int i = 0; i < 1000; i++)
    {
	std::cout << 5 << std::endl;
        // Wait for the timer signal
        siginfo_t si;
        int ret = sigtimedwait(&waitset, &si, &timeout);

    std::cout << 7 << std::endl;

        // Do some computational work
        sum_from_1_to_n(n);
	std::cout << 8 << std::endl;
    }

    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, timed_code, NULL);

    pthread_join(thread, NULL);

    return 0;
}

