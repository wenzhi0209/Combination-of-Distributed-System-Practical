// P4Q3.cpp : Defines the entry point for the console application.
//

#include "omp.h"
#include <stdlib.h>

const int N = 100000;

void fill_rand(int nval, double* A) { //PRODUCER
    for (int i = 0; i < nval; i++) A[i] = (double)rand();
}

double Sum_array(int nval, double* A) { //CONSUMER
    double sum = 0.0;
    for (int i = 0; i < nval; i++) sum = sum + A[i];
    return sum;
}

int mainq3()
{
    double* A, sum, runtime;	
	
	int flag = 0;

    A = (double*)malloc(N * sizeof(double));

    //runtime = omp_get_wtime();
    //fill_rand(N, A);	// Producer: fill an array of data 
    //sum = Sum_array(N, A);	// Consumer: sum the array 
    //runtime = omp_get_wtime() - runtime;


	runtime = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
		{
			fill_rand(N, A);	// Producer: fill an array of data
#pragma omp flush(flag)
			flag = 1;
#pragma omp flush(flag)
		}

//section is run toegther so that use while loop to make a dead lock until condition is fulfil
#pragma omp section
		{
#pragma omp flush(flag)
			while (flag != 1)
			{
#pragma omp flush(flag)	
			}
			
#pragma omp flush(flag)
			sum = Sum_array(N, A);	// Consumer: sum the array
		}
	}

	runtime = omp_get_wtime() - runtime;

    printf(" In %lf seconds, The sum is %lf \n", runtime, sum);

    return 0;
}
