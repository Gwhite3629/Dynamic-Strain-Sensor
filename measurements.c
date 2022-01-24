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
int get_curve(HANDLE fd)
{
    int ret = 0;
    int8_t *data = NULL;
    char c[64];
    int y_off;
    int y_mult;

    CHECK((ret = write_port(fd, "*CLS\r", 5)));
    CHECK((ret = write_port(fd, "ACQUIRE:STATE ON\r", 17)));
    CHECK((ret = write_port(fd, "*OPC\r", 5)));

    MEM(data, (CURVE_SIZE*BIT_SIZE), int8_t);
    printf("Allocated\n");
    CHECK((ret = write_port(fd, "CURVE?\r", 7)));
    printf("Written\n");
    CHECK((ret = read_port(fd, data, (CURVE_SIZE*BIT_SIZE))));
    printf("Read\nData:\n");

    CHECK((ret = write_port(fd, "WFMPRE:YMULT?\r", 14)));
    CHECK((ret = read_port(fd, c, 64)));
    y_mult = atoi(c);
    CHECK((ret = write_port(fd, "WFMPRE:YOFF?\r", 13)));
    CHECK((ret = read_port(fd, c, 64)));
    y_off = atoi(c);

    for(int i = 0; i < (CURVE_SIZE*BIT_SIZE); i++) {
        printf("%d", (data[i]*y_mult) + y_off);
    }
    printf("\n");

exit:
    if (data)
        free(data);

    return ret;
}

// Acquire peak of curve every 5ms
int get_peak(float peak)
{
    int ret = 0;

exit:
    return ret;
}