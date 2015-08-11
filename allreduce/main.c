#include "mpi.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char *argv[])
{
	int size , rank , i;
	int num , sum , temp;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	if(rank == 0){
		num = 5;
	}
	MPI_Bcast(&num , 1 , MPI_INT , 0 , MPI_COMM_WORLD);
	temp = num;
	MPI_Allreduce(&temp , &sum , 1 , MPI_INT , MPI_SUM, MPI_COMM_WORLD);
	printf("Rank %d Sum is : %d\n", rank , sum);
	
	MPI_Finalize();
	return 0;
}