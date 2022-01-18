//  Measurements Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

/*
Functions in this file will send commands and queries.
Currently it is unclear if these should be sent over 2 GPIB channels.
Potentially one channel to send queries and one channel to receive data.
*/

#include <stdlib.h>

#include "utils.h"

int get_curve(float *data)
{
    int ret = 0;
    char *dat = NULL;

    MEM(dat, CURVE_SIZE*BIT_SIZE);

exit:
    if (dat)
        free(dat);

    return ret;
}