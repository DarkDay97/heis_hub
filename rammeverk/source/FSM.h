//State machine 
//This moduel dictates the behavior of the elevator
//
//2019, Audun Birkenes og Jonas Jørgensen

#ifndef FSM_H__
#define FSM_H__

#include "elev.h"

#include <stdlib.h>
#include <time.h>


//The different states of the elevator

typedef enum elev_state {
    INIT_STATE,
    FLOOR_CLOSED,
    FLOOR_OPEN,
    MOVING,
    STATIONARY,
    TEST
} state;

void FSM_init(); //Start-up

void FSM_changeState(); //Change state

int FSM_getState(); //Get current state

void FSM_state_machine(); //function for running the state machine

void FSM_hold_door();

void FSM_drive();

void FSM_drive_from_stationary();

#endif