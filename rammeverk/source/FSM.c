#include "FSM.h"
#include "queue.h"

static state current_state = INIT_STATE;
static const int TIME_LIMIT = 3000;

void FSM_hold_door(){
    int msec = 0;
    clock_t before = clock();
    do {
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        if (elev_get_stop_signal()) {
            msec = 0;
        }
    } while (msec < TIME_LIMIT);
};

void FSM_state_machine(){
    switch (current_state)
    {
    case INIT_STATE:
        elev_set_motor_direction(DIRN_DOWN);
        if (elev_get_floor_sensor_signal() == 0){
            current_state = FLOOR_CLOSED;
            elev_set_motor_direction(DIRN_STOP);
        }
        break;

    case FLOOR_CLOSED:
        /* code */
        if(elev_get_stop_signal()){
            current_state = FLOOR_OPEN;
        }
        break;
    
    case FLOOR_OPEN:
        queue_set_current_floor();
        queue_set_prev_dir();
        FSM_hold_door();
        current_state = FLOOR_CLOSED;
        break;

    case MOVING:
        queue_set_previous_floor();
        queue_should_elev_stop();
        if (elev_get_floor_sensor_signal() + 1){
            current_state = FLOOR_OPEN;
        }
        else if (elev_get_stop_signal()){
            current_state = STATIONARY;
        }
        break;

    case STATIONARY:
        elev_set_motor_direction(DIRN_STOP);
        break;

    case TEST:
    
        break;
        

    default:
        break;
    };
};