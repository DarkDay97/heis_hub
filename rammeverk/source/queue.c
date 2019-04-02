#include "queue.h"

static int orders[10] = {0};

static int prev_floor = -1;
static int current_floor = -1;
static int prev_dir; //1 if elevator previously moved upwards, 0 otherwise. 

int * queue_get_orders(){

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


//Returns 1 if it should stop at the next floor. 
//0 otherwise
int queue_should_elev_stop(int floor, int direction){
    if((current_floor == 0) & (orders[1] | (orders[5] & prev_dir)){
        return 1;
        }
    }
}