#include "mpi.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc, char *argv[])
{
	int size , rank , i;
	int *num; 
	int sum;
	int *count;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	num = (int *)malloc(size * sizeof(int));
	count = (int *)malloc(size * sizeof(int));
	for(i = 0;i<size;i++){
		num[i] = (rank+1);
	}
	for (i = 0; i < size; ++i){
		count[i] = 1;
	}
	MPI_Reduce_scatter(num , &sum , count , MPI_INT , MPI_SUM , MPI_COMM_WORLD);
	printf("Rank %d Sum is : %d\n", rank , sum);
	MPI_Finalize();
	return 0;
}