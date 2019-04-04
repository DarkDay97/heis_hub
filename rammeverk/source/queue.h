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


void queue_add_order(); //Set the number at index to 1
void queue_remove_order(int index); //Set the number at index to 0;

int queue_get_previous_floor();
void queue_set_previous_floor();

int queue_should_stop_at_floor(int floor); //1 if it should stop at the current floor. 0 Otherwise
void queue_set_prev_dir(state current_state);
int queue_get_prev_dir();

//Denne returnerer 1 dersom vi har noen bestillinger. Returnerer 0 ellers.
int queue_have_orders();

void queue_set_current_floor();
int queue_destination();

#endif