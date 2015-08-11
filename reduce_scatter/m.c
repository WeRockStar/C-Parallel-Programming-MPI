#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
 
int main( int argc, char **argv )
{
    int err = 0;
    int *sendbuf, recvbuf, *recvcounts;
    int size, rank, i, sumval;
    MPI_Comm comm;
 
    MPI_Init( &argc, &argv );
    comm = MPI_COMM_WORLD;
    MPI_Comm_size( comm, &size );
    MPI_Comm_rank( comm, &rank );
    sendbuf = (int *) malloc( size * sizeof(int) );
    for (i=0; i<size; i++) 
        sendbuf[i] = rank + i;
    recvcounts = (int *)malloc( size * sizeof(int) );
    for (i=0; i<size; i++) 
        recvcounts[i] = 1;
 
    MPI_Reduce_scatter( sendbuf, &recvbuf, recvcounts, MPI_INT, MPI_SUM, comm );
 
    sumval = size * rank + ((size - 1) * size)/2;
    /* recvbuf should be size * (rank + i) */
    printf("Rank : %d -> %d\n", rank , sumval);
 
    MPI_Finalize( );
    return err;
}