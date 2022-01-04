//  File Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#ifndef _FILE_H_
#define _FILE_H_

#include <windows.h>

int dat_Write(HANDLE dev,
              double Itemp,
              double mag,
              double freq,
              double Ftemp);

#endif //_FILE_H_