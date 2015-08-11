#include "mpi.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char *argv[])
{
	int size , rank , i;
	int num , temp , *recv;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	recv = (int *)malloc(size * sizeof(int));
	if(rank == 0){
		num = 5;
	}
	MPI_Bcast(&num , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
	temp = num;
	MPI_Allgather(&temp , 1 , MPI_INT , recv , 1 , MPI_INT , MPI_COMM_WORLD);
	printf("Rank %d : ", rank);
	for (i = 0; i < size; ++i){
		printf("%d " , recv[i]);
	}
	printf("\n");
	
	MPI_Finalize();
	return 0;
}