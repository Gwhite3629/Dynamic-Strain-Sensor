//  Runtime Control
//  Dynamic Strain Sensor
//  Grady White
//  1/3/22
#include <stdatomic.h>
#include <pthread.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "measurements.h"
#include "file.h"

atomic_int Threshold;
atomic_bool exit;
atomic_bool Trigger;

pthread_mutex_t update;
pthread_mutex_t measure;

static void *update_thresh(void *arg)
{
    int temp_thresh = 0;
    int prev_thresh = 0;

    while(temp_thresh == prev_thresh) {
        prev_thresh = temp_thresh;
        scanf("%d", temp_thresh);
    }

    pthread_mutex_lock(&update);

    Threshold = temp_thresh;

    pthread_mutex_unlock(&update)

fail:
    pthread_exit(NULL);
}

int runtime(HANDLE dev, atomic_int *rate)
{
    time_t start;
    time_t cur;
    double dif;
    double Itemp, mag, freq, Ftemp;

    start = time(NULL);

    while(!exit) {
        usleep(1/(*rate));

        pthread_mutex_lock(&measure);

        //  Record Measurements
        cur = time(NULL);
        dif = difftime(cur, start);
        Itemp = get_temp();
        mag = get_mag();
        if (mag > Threshold) {
            Trigger = 1;
        }
        freq = get_freq();
        Ftemp = get_temp();

        Dat_write();

        pthread_mutex_unlock(&measure);
    }

    return 0;

fail:
    return -1;
}
