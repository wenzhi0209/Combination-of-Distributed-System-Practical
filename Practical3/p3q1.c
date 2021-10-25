#include "stdio.h"
#include "omp.h"
#include "p3q1.h"

int main4() {
	int x = 5;
#pragma omp parallel
	{
		int x = 3;
		
		printf("local shared:x is %d\n", x);
	}
	printf("global shared:x is %d\n", x);
	return 0;
}


int main3() {
	int x = 5;
#pragma omp parallel
	{
		x = x + 1;
		printf("shared:x is %d\n", x);
	}
	printf("Final shared:x is %d\n", x);
	return 0;
}



int main2()
{
#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf("hello(%d)\n", id);

		printf("world(%d)\n", id);
	}
	return 0;
}