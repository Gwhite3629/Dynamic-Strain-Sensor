//  Measurements Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include <stdint.h>
#include <windows.h>

#define FULL 0
#define PART 1
#define SING 2

void part_measure();

void full_measure();

int get_curve(HANDLE fd);

#endif //_MEASUREMENTS_H_