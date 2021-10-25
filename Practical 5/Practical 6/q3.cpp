// mpiexec -np 4 P6Q3

//#include "stdafx.h"
#include <stdio.h>
#include "mpi.h"

int main3(int argc, char** argv)
{
    
    int rank, value, error;


    //mpi initialisation
    MPI_Init(&argc, &argv);

    //mpi commmunication
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    do {
        if (rank == 0)
            scanf_s("%d", &value);

        //Broadcast the input value to all the processes
        MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);

        printf("Process %d got %d\n", rank, value);
        fflush(stdout);
    } while (value >= 0);

    //mpi finalise
    MPI_Finalize();

    return 0;
}