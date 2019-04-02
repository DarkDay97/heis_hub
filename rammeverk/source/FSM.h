//State machine 
//This moduel dictates the behavior of the elevator
//
//2019, Audun Birkenes og Jonas Jørgensen

#ifndef FSM_H__
#define FSM_H__

#include "elev.h"

#include <stdlib.h>


//The different states of the elevator

typedef enum elev_state {
    INIT_STATE,
    FLOOR_CLOSED,
    FLOOR_OPEN,
    MOVING,
    STATIONARY
} state;

void FSM_init(); //Start-up

void FSM_changeState(); //Change state

int FSM_getState(); //Get current state

#endif