#include "FSM.h"
#include "queue.h"
#include "timer.h"
#include "lights.h"

state current_state = INIT_STATE;

//Function to hold the door open while the stop button is pressed

void FSM_drive(){
    if (queue_destination() > (elev_get_floor_sensor_signal() + 1)){
        elev_set_motor_direction(DIRN_UP);
        queue_set_prev_dir(current_state, UP);
    } else if (queue_destination() < elev_get_floor_sensor_signal()){
        elev_set_motor_direction(DIRN_DOWN);
        queue_set_prev_dir(current_state, DOWN);
    } else{
        elev_set_motor_direction(DIRN_STOP); //redundant but why not
    }
};

void FSM_drive_from_stationary(){
    if (queue_get_prev_dir() == UP){
        if (queue_destination() > (queue_get_previous_floor() + 1)){
            elev_set_motor_direction(DIRN_UP);
            queue_set_prev_dir(current_state, UP);
        } else if (queue_destination() <= (queue_get_previous_floor() + 1)){
            elev_set_motor_direction(DIRN_DOWN);
            queue_set_prev_dir(current_state, DOWN);
        } else{
            elev_set_motor_direction(DIRN_STOP); //redundant but why not
        }
    } else if (queue_get_prev_dir() == DOWN){
        if (queue_destination() >= (queue_get_previous_floor() + 1)){
            elev_set_motor_direction(DIRN_UP);
            queue_set_prev_dir(current_state, UP);
        } else if (queue_destination() < (queue_get_previous_floor() + 1)){
            elev_set_motor_direction(DIRN_DOWN);
            queue_set_prev_dir(current_state, DOWN);
        } else{
            elev_set_motor_direction(DIRN_STOP); //redundant but why not
        }
    }
};


//The overview of the different states and moving between them
void FSM_state_machine(){
    queue_add_order();

    switch (current_state)
    {
    case INIT_STATE:
        elev_set_motor_direction(DIRN_DOWN);
        queue_remove_all_orders();
        if (elev_get_floor_sensor_signal() == 0){
            current_state = FLOOR_CLOSED;
            queue_set_current_floor();
            elev_set_motor_direction(DIRN_STOP);
            timer_init();

        }
        break;

    case FLOOR_CLOSED:
        if(elev_get_stop_signal()){
            current_state = FLOOR_OPEN;
        } else if (queue_have_orders()){
            current_state = MOVING;
            FSM_drive();
            queue_set_previous_floor();
        } else if (!queue_have_orders()){
            queue_set_prev_dir(current_state, NONE);
        }
        break;
    
    case FLOOR_OPEN:
        queue_remove_order();
        
        if(timer_is_timeout()){
            current_state = FLOOR_CLOSED;
        }
        else if (elev_get_stop_signal()){
            timer_reset();
        }
        break;

    case MOVING:
        if ((elev_get_floor_sensor_signal() + 1)){
            if(queue_should_stop_at_floor(elev_get_floor_sensor_signal())){
                elev_set_motor_direction(DIRN_STOP);
                queue_set_current_floor();
                lights_set_floor_indicator();
                timer_reset();
                current_state = FLOOR_OPEN;
                if((elev_get_floor_sensor_signal() == 0) | (elev_get_floor_sensor_signal() == 3)){
                    queue_set_prev_dir(current_state ,NONE);
                }
            }
        }
        else if (elev_get_stop_signal()){
            elev_set_motor_direction(DIRN_STOP);
            queue_remove_all_orders();
            current_state = STATIONARY;
        }
        break;

    case STATIONARY:
        if (elev_get_stop_signal()){
            queue_remove_all_orders();
        } else if (queue_have_orders()){
            current_state = MOVING;
            FSM_drive_from_stationary();
        }
        break;

   /* case TEST:
        elev_set_motor_direction(DIRN_UP);
        if(elev_get_floor_sensor_signal()+1){
            current_state = FLOOR_OPEN;
            elev_set_motor_direction(DIRN_STOP);
        }
        break;
     */   

    default:
        break;
    };
};