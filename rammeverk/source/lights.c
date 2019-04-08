#include "lights.h"


void lights_set_floor_indicator(){
    elev_set_floor_indicator(queue_get_current_floor());
}

