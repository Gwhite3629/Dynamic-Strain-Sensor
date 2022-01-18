//  Setup
//  Dynamic Strain Sensor
//  Grady White
//  1/5/22

#include <windows.h>

#include "utils.h"
#include "serial.h"

#define DIV "CH1:SCALE 100E-3\r"

int init(HANDLE fd)
{
    int ret = 0;


    CHECK(ret = write_port(fd, "*CLS\r", 5));
    CHECK(ret = write_port(fd, "CURsor:SELect:SOUrce CH1\r", 25));
    CHECK(ret = write_port(fd, "CALibrate:INTERNAL\r", 19));
    CHECK(ret = write_port(fd, "CH1:COUPLING DC\r", 16));
    CHECK(ret = write_port(fd, DIV, 17));


exit:
    return ret;
}