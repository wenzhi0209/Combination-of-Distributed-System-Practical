// P7Q3.cpp : Defines the entry point for the console application.
//

#include "stdio.h"


int main3()
{
    int a = 1;
    int b = 2;
    int c = 4;

#pragma omp parallel firstprivate(a) 
    {
        a = a + b;
      
    }

    printf("\n\nRESULT APPLYING FIRSTPRIVATE\n");
    printf("Value a : %i\n", a);
    printf("Value b : %i\n", b);
    printf("Value c : %i\n", c);

#pragma omp parallel 
    {
        a = a + b;
       
    }
    printf("\n\nRESULT WITHOUT APPLYING FIRSTPRIVATE\n");
    printf("Value a : %i\n", a);
    printf("Value b : %i\n", b);
    printf("Value c : %i\n", c);

    return 0;
}