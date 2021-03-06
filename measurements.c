//  Measurements Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

/*
Functions in this file will send commands and queries.
Currently it is unclear if these should be sent over 2 GPIB channels.
Potentially one channel to send queries and one channel to receive data.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "utils.h"
#include "serial.h"

// Acquire entire data curve every 5ms
int get_curve(HANDLE fd, float **output)
{
    int ret = 0;
    int8_t *data = NULL;
    char c[80];
    float y_off;
    float y_mult;
    float y_zero;

    CHECK((ret = write_port(fd, "*CLS\r", 5)));
    CHECK((ret = write_port(fd, "ACQUIRE:STATE ON\r", 17)));
    CHECK((ret = write_port(fd, "*OPC\r", 5)));
    CHECK((ret = write_port(fd, "HEADER OFF\r", 11)));

    MEM(data, (CURVE_SIZE*BIT_SIZE), int8_t);
    printf("Allocated\n");
    CHECK((ret = write_port(fd, "CURVE?\r", 7)));
    printf("Written\n");
    CHECK((ret = read_port(fd, data, (CURVE_SIZE*BIT_SIZE))));
    printf("Read\nData:\n");

    memset(c, 0, 80);
    CHECK((ret = write_port(fd, "WFMPRE:YOFF?;YMULT?;YZERO?\r", 27)));
    CHECK((ret = read_port(fd, c, 80)));

    sscanf(c, "%e;%e;%e", &y_off, &y_mult, &y_zero);

    //y_off = ReverseFloat(y_off);
    //y_mult = ReverseFloat(y_mult);
    //y_zero = ReverseFloat(y_zero);

    printf("y_off %e\ny_mult %e\ny_zero %e\n", y_off, y_mult, y_zero);

    for(int i = 0; i < (CURVE_SIZE*BIT_SIZE); i++) {
        (*output)[i] = (((float)data[i]-y_off) * y_mult) - y_zero;
        printf("%f", (*output)[i]);
    }

exit:
    if (data)
        free(data);

    return ret;
}
/*
int full_measure()
{
    int ret = 0;

exit:
    return ret;
}

int part_measure()
{
    int ret = 0;

exit:
    return ret;
}
*/