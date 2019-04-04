#include "FSM.h"
#include "queue.h"

static state current_state = INIT_STATE;
static const int TIME_LIMIT = 3000;

//Function to hold the door open while the stop button is pressed
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

void FSM_drive(){
    if (queue_destination() > elev_get_floor_sensor_signal() + 1){
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
        if (queue_destination() > queue_get_previous_floor() + 1){
            elev_set_motor_direction(DIRN_UP);
            queue_set_prev_dir(current_state, UP);
        } else if (queue_destination() <= queue_get_previous_floor() + 1){
            elev_set_motor_direction(DIRN_DOWN);
            queue_set_prev_dir(current_state, DOWN);
        } else{
            elev_set_motor_direction(DIRN_STOP); //redundant but why not
        }
    } else if (queue_get_prev_dir() == DOWN){
        if (queue_destination() >= queue_get_previous_floor() + 1){
            elev_set_motor_direction(DIRN_UP);
            queue_set_prev_dir(current_state, UP);
        } else if (queue_destination() < queue_get_previous_floor() + 1){
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
        if (elev_get_floor_sensor_signal() == 0){
            current_state = FLOOR_CLOSED;
            queue_set_current_floor();
            elev_set_motor_direction(DIRN_STOP);
        }
        break;

    case FLOOR_CLOSED:
        if(elev_get_stop_signal()){
            current_state = FLOOR_OPEN;
        } else if (queue_have_orders()){
            current_state = MOVING;
            queue_set_previous_floor();
            FSM_drive();
        }
        break;
    
    case FLOOR_OPEN:
        queue_remove_order();
        FSM_hold_door();
        current_state = FLOOR_CLOSED;
        break;

    case MOVING:
        if (elev_get_floor_sensor_signal() + 1){
            if(queue_should_stop_at_floor(elev_get_floor_sensor_signal())){
                elev_set_motor_direction(DIRN_STOP);
                queue_set_current_floor();
                current_state = FLOOR_OPEN;
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

    case TEST:
        elev_set_motor_direction(DIRN_UP);
        if(elev_get_floor_sensor_signal()+1){
            current_state = FLOOR_OPEN;
            elev_set_motor_direction(DIRN_STOP);
        }
        break;
        

    default:
        break;
    };
};