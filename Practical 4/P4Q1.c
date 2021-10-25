#include "stdio.h"
#include "omp.h"
#define NUM_THREADS 4
static long num_steps = 100000;
double step;

int mainq1()
{
	int i, nthreads;
	double pi = 0;
	
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	double start_time = omp_get_wtime();
#pragma omp parallel
	{
		double sum = 0.0;
		int i, id, nthrds;
		double x=0;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		if (id == 0) nthreads = nthrds;

		for (i = id, sum = 0.0; i < num_steps; i = i + nthrds)
		{
			x = (i + 0.5) * step;
			sum += 4.0 / (1.0 + x * x);
		}

#pragma omp critical
		pi += sum * step;
	}

	double end_time = omp_get_wtime();

	printf("%f\n", pi);

	printf("Work took %f seconds\n", end_time - start_time);
	return 0;
}