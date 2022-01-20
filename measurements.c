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
    char *dat = NULL;
    int8_t *data = NULL;
    char c[1];
    char recordl[8];
    int lgth_num;
    int length;

    MEM(data, CURVE_SIZE*BIT_SIZE, int8_t);
    printf("Allocated\n");
    CHECK((ret = write_port(fd, "CURVE?\r", 8)));
    printf("Written\n");
    CHECK((ret = query(fd, c, 1)));
    CHECK((ret = query(fd, c, 1)));
    lgth_num = atoi(c);
    CHECK((ret = query(fd, recordl, lgth_num)));
    printf("lgth_num: %d\n");
    recordl[lgth_num] = '\0';
    length = atoi(recordl);
    printf("Length: %d\n", length);
    MEM(dat, (length), char)
    CHECK((ret = query(fd, dat, (length))));
    printf("Read\n");
    for(int i = 0; i < (length); i++) {
        printf("Data[%d]: %c\n", i, dat[i]);
    }

exit:
    if (dat)
        free(dat);
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