//  GPIB Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#ifndef _GPIB_PROF_H_
#define _GPIB_PROF_H_

#include <windows.h>

#define CHECK(ret) \
    if (ret < 0) \
        goto exit;

int def(HANDLE fd);

#endif //_GPIB_PROF_H_