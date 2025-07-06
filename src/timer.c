#include "timer.h"
#include "stdint.h"

#ifdef UNIX
#include <time.h>

struct timespec start_time;

void timer_start()
{
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

Duration timer_stop()
{
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    time_t delta_s = (end_time.tv_sec - start_time.tv_sec);
    uint64_t delta_us = (end_time.tv_nsec - start_time.tv_nsec) / 1000;
    uint64_t delta_ms = delta_us / 1000;
    delta_us -= delta_ms * 1000;

    return (Duration)
    {
        .seconds = delta_s,
        .millis = delta_ms,
        .micros = delta_us
    };
}
#elif defined(WIN32)
#include <sys/timeb.h>

struct timeb start_time;

void timer_start()
{
    ftime(&start_time);
}

Duration timer_stop()
{
    struct timeb end_time;
    ftime(&end_time);
    
    unsigned int delta_s = (unsigned int) (end_time.time - start_time.time);
    unsigned short delta_ms = end_time.millitm >= start_time.millitm
        ? end_time.millitm - start_time.millitm
        : 1000 - start_time.millitm + end_time.millitm;

    return (Duration)
    {
        .seconds = delta_s,
        .millis = delta_ms,
        .micros = 0
    };
}
#endif