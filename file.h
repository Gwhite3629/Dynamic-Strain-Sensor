//  File Header
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#ifndef _FILE_H_
#define _FILE_H_

#include <windows.h>

#define FAULT -1

#define MEM_ERROR "memory error"
#define FILE_ERROR "file error"

#define uint unsigned int

typedef struct AVERAGE_DATA{
    float AVERAGE_THRESHOLDS[6];
    uint WINDOW_SIZE;
} AVERAGE_DATA;

typedef struct config {
    AVERAGE_DATA AVERAGE_DATA;
    float PEAK_THRESHOLD;
    uint SAMPLE_FREQUENCY;
} config;

#define VALID(check, code) \
    if (check == NULL) { \
        perror(code); \
        ret = FAULT; \
        goto exit; \
    }

//  Generic function to allocate, allign, and check faults in memory
#define MEM(ptr, size) \
    ptr = malloc(size); \
    VALID(ptr, MEM_ERROR); \
    memset(ptr, 0, size);

//  Generic function to find a string in a file and return its location.
int find_event(FILE *fd,
               fpos_t *prof_start,
               char *locator);

//  Acquires data from config file and puts it into a struct
int get_config(config *config,
               char *name);

//  Template for data write
int dat_Write(HANDLE dev,
              double Itemp,
              double mag,
              double freq,
              double Ftemp);

#endif //_FILE_H_