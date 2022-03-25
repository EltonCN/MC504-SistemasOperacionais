/**
 * @file smooth.c
 * @author EltonCN (elton.nascimento@students.ic.unicamp.br)
 * @brief Example of pthread performing the filtering of a time series using a convolution filter.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define n_data 7784 //7786;
#define n_thread 4 //=Processor count
const float sigma = 1.0; //Filter standard deviation

float times[n_data]; //Data time
float data[n_data]; //Data
float smoothed[n_data]; //Smoothed result

/**
 * @brief Filters a piece of data using a gaussian convolution filter 
 * 
 * @param thread_id The thread ID, is a integer as a void pointer.
 * @return void* Nothing
 */
void* smooth(void* thread_id)
{
    int id = (int) thread_id; //Converts the void pointer back to an int

    //Check which piece of data to filter
    int init = id*(n_data/n_thread);
    int end = (id+1)*(n_data/n_thread);

    //Stores the kernel of convolution
    float kernel[n_data];

    for(int i = init; i<end; i++)
    {
        float frame_time = times[i]; //Filtering frame time
        smoothed[i] = 0.0; //Initialize the result
        
        float kernel_sum = 0.0; 
        
        //Computes the convolution kernel
        for(int j = 0; j<n_data; j++)
        {
            float time = times[j];
            kernel[j] = exp(  -pow(frame_time - time, 2.0)  /  (2.0*pow(sigma, 2.0)) );
            kernel_sum += kernel[j];
        }

        //Computes the frame smoothed data convoluting the data with the kernel
        for(int j = 0; j<n_data; j++)
        {
            smoothed[i] += data[j]*kernel[j]/kernel_sum;
        }
    }

    
}

/**
 * @brief Reads a data file
 * 
 * @param file_name The file to read 
 * @param vector The vector to save the data
 * @param n Data size
 */
void read_data(char* file_name, float* vector, int n)
{
    FILE *file;

    file = fopen(file_name, "r");

    if(file == NULL)
    {
        printf("ERROR: File error. Exiting\n");
        exit(1);
    }  

    for(int i = 0; i<n_data; i++)
    {
        float d;
        fscanf(file, "%f", &d);
        vector[i] = d;
    }

}

/**
 * @brief Saves the smoothed result to a file
 * 
 */
void save_smoothed()
{
    FILE *file;

    file = fopen("Smoothed.txt", "w");

    for(int i = 0; i<n_data; i++)
    {
        fprintf(file, "%f", smoothed[i]);

        if(i != n_data-1)
        {
            fprintf(file, "\n");
        }
    }
}

int main()
{   
    //Read data
    read_data("Data.txt", data, n_data);
    read_data("Time.txt", times, n_data);

    clock_t start, end;
    double deltaT;
    pthread_t threads[n_thread];

    start = clock(); //Start time

    //Initialize threads
    for(int i = 0; i<n_thread; i++)
    {
        pthread_create(&threads[i], NULL, smooth, (void*) i);
    }

    //Wait for completion
    for(int i = 0; i<n_thread; i++)
    {
        pthread_join(threads[i], NULL);
    }

    //Compute and displays the time taken to filter the data
    end = clock();
    deltaT = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("Smoothed the data in %.2f s\n", deltaT);

    //Save thre results
    save_smoothed();

    return 0;
}