#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
 
int main( int argc, char **argv )
{
    int size, rank;
    MPI_Comm comm;
    MPI_Init( &argc, &argv );
    comm = MPI_COMM_WORLD;
    MPI_Comm_size( comm, &size );
    MPI_Comm_rank( comm, &rank );
    MPI_Barrier(comm);
    MPI_Finalize();
    return 0;
}