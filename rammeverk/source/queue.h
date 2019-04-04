#ifndef QUEUE_H__
#define QUEUE_H__

#include "elev.h"
#include <stdio.h>
#include <assert.h>

typedef enum prev_motor_dir{
    DOWN =-1,
    NONE = 0,
    UP = 1
} prev_motor_dir;


int * queue_get_orders(); //Returns an int array with the current orders
void queue_add_order(int index); //Sett the number at place index = 1

int queue_get_previous_floor();
void queue_set_previous_floor();

int queue_should_stop_at_floor(int floor, int prev_dir); //1 if it should stop at the current floor. 0 Otherwise
void queue_set_prev_dir(state current_state);
int queue_get_prev_dir();

int queue_have_orders();

void queue_set_current_floor();
int queue_destination();

#endif