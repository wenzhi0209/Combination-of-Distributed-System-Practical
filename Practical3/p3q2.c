
/*

This program will numerically compute the integral of

4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The program was parallelized using OpenMP by adding just
four lines

(1) A line to include omp.h -- the include file that
contains OpenMP's function prototypes and constants.

(2) A pragma that tells OpenMP to create a team of threads

(3) A pragma to cause one of the threads to print the
number of threads being used by the program.

(4) A pragma to split up loop iterations among the team
of threads.  This pragma includes 2 clauses to (1) create a
private variable and (2) to cause the threads to compute their
sums locally and then combine their local sums into a
single global value.


*/

#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
double step;
int notmain()
{
	int i;
	double x, pi, sum = 0.0;
	double start_time, run_time;

	step = 1.0 / (double)num_steps;
	for (i = 1; i <= 100; i++) {
		sum = 0.0;
		omp_set_num_threads(i);
		start_time = omp_get_wtime();
#pragma omp parallel  
		{
#pragma omp single
			printf(" num_threads = %d", omp_get_num_threads());

#pragma omp for reduction(+:sum)
			for (i = 1; i <= num_steps; i++) {
				x = (i - 0.5) * step;
				sum = sum + 4.0 / (1.0 + x * x);
			}
		}
		pi = step * sum;
		run_time = omp_get_wtime() - start_time;
		printf("\n pi is %f in %f seconds and %d threads\n", pi, run_time, i);
	}
}


/*
#include "omp.h"
#define PAD 8 //assume 64 byte L1 cache line size
#define NUM_THREADS 2
static long num_steps = 100000;
double step;
*/


/*
int main2b()
{
	int i, nthreads;
	double pi, sum[NUM_THREADS][PAD];
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double start_time = omp_get_wtime();
#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0) nthreads = nthrds;

		for (i = id, sum[id][0] = 0.0; i < num_steps; i = i + nthrds)
		{
			x = (i + 0.5) * step;
			sum[id][0] += 4.0 / (1.0 + x * x);
		}
	}
	double end_time = omp_get_wtime();
	for (i = 0, pi = 0.0; i < nthreads; i++) {
		pi += sum[i][0] * step;
	}
	printf("%f\n", pi);

	printf("Work took %f seconds\n", end_time - start_time);
	return 0;
}

int main2a()
{
	int i, nthreads=0;
	double pi, sum[NUM_THREADS];
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double start_time = omp_get_wtime();

#pragma omp parallel
	{
		int i, id, nthrds;
		double x;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		
		if (id == 0) nthreads = nthrds;

		for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds)
		{
			x = (i + 0.5) * step;
			sum[id] += 4.0 / (1.0 + x * x);
		}
	}

	double end_time = omp_get_wtime();
	for (i = 0, pi = 0.0; i < nthreads; i++) {
		pi += sum[i] * step;
	}
	printf("%f\n", pi);

	printf("Work took %f seconds\n", end_time - start_time);
	return 0;
}

*/