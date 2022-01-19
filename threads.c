//  Thread Functions
//  Dynamic Strain Sensor
//  Grady White
// 1/7/22

#include <stdio.h>
#include <string.h>

#include "threads.h"

void *quit_condition(void *arg)
{
    char detect[64];

    while(!exit_runtime) {
        scanf("%s", detect);
        if (strcmp(detect, "quit") ==  0)
            exit_runtime = 1;
    }
}

void *time_measure(void *arg)
{

}