// solution
// P4Q2.cpp : Defines the entry point for the console application.
//
// 
//critical

#include "omp.h"
#include "stdio.h"
#define NUM_THREADS 8
const long MAX = 100000;


int maincri()
{
	double ave = 0.0, A[MAX];
	int i, nthreads;
	double total_sum = 0.0;

	for (i = 0; i < MAX; i++)
	{
		A[i] = i;
	}
	omp_set_num_threads(NUM_THREADS);
	double start_time = omp_get_wtime();

#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		double sum;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();

		if (id == 0) nthreads = nthrds;

		for (i = id, sum = 0.0; i < MAX; i = i + nthrds) {
			sum += A[i];
		}

#pragma omp critical
		total_sum += sum;
	}
	ave = total_sum / MAX;
	double end_time = omp_get_wtime();
	printf("%f\n", ave);
	printf("Work took %f seconds\n", end_time - start_time);
	return 0;
}



// P4Q2.cpp : Defines the entry point for the console application.
//


//#include "omp.h"
//#include "stdio.h"
//#define NUM_THREADS 8
//const long MAX = 100000;

// reduction

int mainered()
{
	double ave = 0.0, A[MAX];
	int i;
	for (i = 0; i < MAX; i++)
	{
		A[i] = i;
	}
	double start_time = omp_get_wtime();

#pragma omp parallel for reduction(+:ave)
	for (i = 0; i < MAX; i++) {
		ave += A[i];
	}

	ave = ave / MAX;
	double end_time = omp_get_wtime();

	printf("%f\n", ave);
	printf("Work took %f seconds\n", end_time - start_time);
	return 0;
}

