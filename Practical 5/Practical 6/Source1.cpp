#include<iostream>
#include<mpi.h>
using namespace std;

int main(int argc, char** argv) {
    int id, nproc;
    int sum, accum, startval, endval;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);  // get number of total nodes
    MPI_Comm_rank(MPI_COMM_WORLD, &id);     // get id of mynode
    sum = 0; // zero sum for accumulation
    //startval = 10000*id/nproc+1;
    //endval =   10000*(id+1)/nproc;
    for (int i = 1 + id; i <= 10000; i += nproc) // loop splitting
        sum = sum + i;
    cout << "I am the node " << id << "; the partial sum is: " << sum << endl;
    if (id != 0)
        MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    else
        for (int j = 1; j < nproc; j = j + 1) {
            //MPI_Recv(&accum,1,MPI_INT,j,1,MPI_COMM_WORLD, &status);
            MPI_Recv(&accum, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
                &status);
            // we do not wait for particular slave: recieve answer from anybody
            sum = sum + accum;
            cout << "The sum yet is: " << sum << endl;
        }
    if (id == 0)
        cout << "The sum is: " << sum << endl;
    MPI_Finalize();
}