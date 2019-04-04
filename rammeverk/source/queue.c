#include "queue.h"


static int orders[12] = {0};

static int prev_floor = -1;
static int current_floor = -1;
static prev_motor_dir prev_dir;


int queue_have_orders(){
    for (int i = 0; i < 12; i++){
        if (orders[i]){
            return 1;
        }
    }
    return 0;
};


void queue_add_order(){
    for(int i = 0, j = 0; i<12; i+=3, j++){
        orders[i] += elev_get_button_signal(1, j);
        orders[i+1] += elev_get_button_signal(2, j);
        orders[i+2] += elev_get_button_signal(0,j);
    }
};

void queue_remove_order(){
    orders[1 + current_floor*3] = 0;
    if (prev_dir == UP){
        orders[1 + current_floor*3 + 1] = 0;
    }
    else if (prev_dir == DOWN) {
        orders[1 + current_floor - 1] = 0;
    }
}

int queue_get_previous_floor(){
 return prev_floor;
};

void queue_set_previous_floor(){
  prev_floor = current_floor;
};

void queue_set_current_floor(){
  current_floor = elev_get_floor_sensor_signal();
};

void queue_set_prev_dir(state current_state){
    if(current_floor > prev_floor){
        prev_dir = UP;
    } else if (current_floor < prev_floor) {
        prev_dir = DOWN;
    }
    if ((!queue_have_orders()) & (current_state == FLOOR_CLOSED)){
        prev_dir = NONE;
    }
};

prev_motor_dir queue_get_prev_dir(){
    return prev_dir;
}


//Returns 1 if it should stop at the next floor. 
//0 otherwise
int queue_should_stop_at_floor(int floor){
    if (orders[1+floor*3] | orders[1+floor*3+prev_dir]){
        return 1;
    } 
    else {
        return 0;
    }
};

int queue_destination(){
    static int destination;
    if (prev_dir == UP){
        if (orders[9] | orders[10]){
            destination = 4;
        } else if (orders[7] | orders[8]){
            destination = 3;
        }
    } else if (prev_dir == DOWN){
        if (orders[1] | orders[2]){
            destination = 1;
        } else if (orders[3] | orders[4]){
            destination = 2;
        }
    } else if (prev_dir == NONE){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 3; j++){
                if (orders[3*i + j]){
                    destination = i + 1;
                }
            }
        }
    }
    return destination;
};