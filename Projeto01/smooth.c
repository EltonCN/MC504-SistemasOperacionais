#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

float times[];
float data[];
float smoothed[];

const float sigma = 10.0;

int n_data;
int n_thread;

void* smooth(void* thread_id)
{
    int id = (int) thread_id;

    //Colocar for para escolher o frame
    float frame_time = times[];
    smoothed[] = 0.0;
    for(int j = 0; j<n_data; j++)
    {
        float time = times[j]
        float kernel = exp(-pow(frame_time - time), 2.0)/(2.0*pow(sigma, 2));

        smoothed[] += data[j]*kernel;
    }
}