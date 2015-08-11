#include "mpi.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
void printNum(int *n , int num){
	int i;
	for (i = 0; i < num; ++i)
	{
		printf("%d ", n[i]);
	}
	printf("\n");
}
int main(int argc, char *argv[])
{
	int size , rank ,i;
	int *data , *recv_data , sum = 0;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);

	data = (int *) malloc(20 * sizeof(int));
	recv_data = (int *)malloc(20 * sizeof(int));
	if(rank == 0){
		for(i = 0;i < 4;i++){
			data[i] = (i+1);
		}
		printf("Rank = %d : ", rank);
		for(i = 0;i<4;i++){
			printf("%d ", data[i]);
		}
		printf("\n");
	}
	MPI_Scatter(data , 4, MPI_INT , recv_data , 4 , MPI_INT , 0 , MPI_COMM_WORLD);
	if(rank != 0){
		printf("Rank = %d : ", rank);
		printNum(recv_data , 4);
	}
	MPI_Finalize();
	return 0;
}