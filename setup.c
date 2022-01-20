//  Setup
//  Dynamic Strain Sensor
//  Grady White
//  1/5/22

#include <windows.h>
#include <stdio.h>

#include "utils.h"
#include "serial.h"

#define DIV "CH1:SCALE 100E-3\r"

int init(HANDLE fd)
{
    int ret = 0;
    char dat[64];

    CHECK((ret = write_port(fd, "*CLS\r", 6)));
    CHECK((ret = write_port(fd, "ACQUIRE:STATE ON\r", 18)));
    CHECK((ret = write_port(fd, "*OPC\r", 6)));
    CHECK((ret = write_port(fd, "CURSOR:SELect:SOUrce CH1\r", 26)));
    CHECK((ret = write_port(fd, "CALIBRATE:INTERNAL\r", 20)));
    CHECK((ret = write_port(fd, "CH1:COUPLING DC\r", 17)));
    CHECK((ret = write_port(fd, DIV, 18)));
    CHECK((ret = write_port(fd, "HORIZONTAL:SCALE 5E-3\r", 23)));
    CHECK((ret = write_port(fd, "DATA:SOURCE CH1\r", 17)));
    CHECK((ret = write_port(fd, "DATA:START 1\r", 14)));
    CHECK((ret = write_port(fd, "DATA:STOP 2500\r", 16)));  
    CHECK((ret = write_port(fd, "DATA:WIDth 1\r", 14)));
    CHECK((ret = write_port(fd, "DATA:ENCDG ASCII\r", 18)))

exit:
    return ret;
}