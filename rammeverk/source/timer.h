#ifndef TIMER_H__
#define TIMER_H__

#include <time.h>

void timer_init(); //Initialize timer by resetting it

void timer_reset(); //Resets timer

int timer_is_timeout(); //Checks if the timer has surpassed 3 secounds

#endif