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

#define HYSTERESIS_TIME 2

atomic_int Threshold;
atomic_bool exit_flag = 0;
atomic_bool Trigger = 0;

pthread_mutex_t update = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t measure = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wait = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

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

    pthread_mutex_unlock(&update);

fail:
    pthread_exit(NULL);
}

static void *timer(void *arg) {
    bool *delay = (bool *)arg;

    struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += (60 * HYSTERESIS_TIME)



    pthread_testcancel();
    pthread_mutex_lock(&wait);
    pthread_cond_timedwait(&cond, &wait, )
    pthread_mutex_unlock(&wait);
}

static void *hysteresis(void *arg)
{
    pthread_t thr;
    bool delay;

    pthread_create(&thr, NULL, &timer, (void *)delay);

    while(!exit) {
        if (Trigger) {
            if (delay) {

            }
        }
    }
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

        dat_Write(dev,
                  Itemp,
                  mag,
                  freq,
                  Ftemp);

        pthread_mutex_unlock(&measure);
    }

    return 0;

fail:
    return -1;
}