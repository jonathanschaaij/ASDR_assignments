#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <iostream>
#include <fstream>

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
	int count = 1000;
    struct timespec time[count + 1];
    clock_gettime(CLOCK_MONOTONIC, &time[0]);

    for (size_t i = 0; i < count; i++)
    {
        // Do some calc
        sum_from_1_to_n(1000000);
        // Sleep for 1ms
        nanosleep((const struct timespec[]){{0, 1000000L}}, NULL);

        // Log the time
        clock_gettime(CLOCK_MONOTONIC, &time[i + 1]);
    }

    std::ofstream myfile;            // create output file stream
    myfile.open("time_sleep_" + std::to_string(time[0].tv_sec) + ".csv"); // open file for writing

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

    status = pthread_create(&thread_id, NULL, empty_thread_function, NULL);
    status = pthread_join(thread_id, NULL);

    return 0;
}
