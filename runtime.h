//  Runtime Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#include <windows.h>

//  Flags to determine which type of measurement is being taken
#define GENERIC_MEASUREMENT 0
#define PEAK_MEASUREMENT 1
#define MOVING_AVERAGE_MEASUREMENT 2

int runtime(HANDLE dev);

#endif //_RUNTIME_H_