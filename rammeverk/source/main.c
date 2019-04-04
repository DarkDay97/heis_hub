#include "elev.h"
#include "FSM.h"
#include "queue.h"

#include <stdio.h>


//comment
int main() {

    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    

    while (1) {

        FSM_state_machine();
        if (elev_get_obstruction_signal()){
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
