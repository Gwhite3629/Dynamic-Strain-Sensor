//  Runtime Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22

#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "measurements.h"
#include "file.h"
#include "threads.h"

int runtime(HANDLE dev)
{
    int ret = 0;
    int pos;
    int barrier = 0; // Current threshold
    int prev_barrier = 0; // Previous threshold

    float *window;

    float sum = 0;
    float current_mag;
    float avg;

    pthread_t thr;

    // Get config data
    Config *config;
    char name[64] = "DEFAULT";
    printf("Enter config name:\n");
    scanf("%s", name);
    get_config(config, name);

    HANDLE_ERR((ret = pthread_create(&thr, NULL, &quit_condition, NULL)), "pthread_create");

    // Setup window
    int pos_max = config->AVERAGE_DATA.WINDOW_SIZE;
    MEM(window, pos_max, float);

    // Main runtime loop
    while(!exit_runtime) {
        // Get most recent strain
        current_mag = get_mag();
        // Average the strain
        avg = moving_average(window,config->AVERAGE_DATA.WINDOW_SIZE, &sum, pos, current_mag);
        // Increase location in window
        pos++;
        // Wrap window
        if (pos>=pos_max)
            pos = 0;

        // Measurement conditions (non-timer)
        if (current_mag>config->PEAK_THRESHOLD) {
            part_measure();
        } else if (avg>config->AVERAGE_DATA.AVERAGE_THRESHOLDS[barrier]) {
            if (barrier < 5)
                barrier++;
            full_measure();
        } else if (avg<config->AVERAGE_DATA.AVERAGE_THRESHOLDS[prev_barrier]) {
            barrier--;
        }
        usleep(1000000*(1/config->SAMPLE_FREQUENCY));
    }

exit:
    if (window)
        free(window);

    return ret;
}