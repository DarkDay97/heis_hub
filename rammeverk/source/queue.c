#include "queue.h"

static int orders[10] = {0};

static int prev_floor = -1;
static int current_floor = -1;
static int prev_dir; //1 if elevator previously moved upwards, 0 otherwise. 

int * queue_get_orders(){
return 0;
};

void queue_add_order(int index){
    orders[index] = 1;
};

int queue_get_previous_floor(){
 return prev_floor;
};

void queue_set_previous_floor(){
  prev_floor = current_floor;
};

void queue_set_current_floor(){
  current_floor = elev_get_floor_sensor_signal();
};

void queue_set_prev_dir(){
    if(current_floor > prev_floor){
        prev_dir = 1;
    } else {
        prev_dir = 0;
    }
};

int queue_get_prev_dir(){
    return prev_dir;
}


//Returns 1 if it should stop at the next floor. 
//0 otherwise
int queue_should_stop_at_floor(int floor, int prev_dir){
    if (orders[floor*3] | orders[floor*3+prev_dir]){
        return 1;
    } 
    else {
        return 0;
    }
};