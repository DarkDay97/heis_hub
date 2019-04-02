#include "FSM.h"
#include "queue.h"

static state current_state = STATIONARY;


switch (current_state)
{
    case INIT_STATE:
        /* code */
        break;

    case FLOOR_CLOSED:
        /* code */
        break;
    
    case FLOOR_OPEN:
        queue_set_current_floor();
        queue_set_prev_dir();
        break;

    case MOVING:
        queue_set_previous_floor();
        queue_should_elev_stop();
        if (elev_get_floor_sensor_signal + 1){
            current_state = FLOOR_OPEN;
        }
        else if (elev_get_stop_signal()){
            current_state = STATIONARY;
        }
        break;

    case STATIONARY:
        elev_set_motor_direction(DIRN_STOP)
        break;
        

    default:
        break;
};