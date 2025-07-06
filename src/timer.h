#include "stddef.h"

typedef struct Duration
{
    unsigned int seconds;
    unsigned short millis;
    unsigned short micros;
} Duration;

void timer_start();

Duration timer_stop();