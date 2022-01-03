//  Measurements Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#ifndef _MEASUREMENTS_H_
#define _MEASUREMENTS_H_

#include <stdint.h>

//  Returns dynamic strain magnitude
double get_mag();
//  Returns dynamic strain frequency
double get_freq();
//  Returns temperature reading from thermocouple
float get_temp();

#endif //_MEASUREMENTS_H_