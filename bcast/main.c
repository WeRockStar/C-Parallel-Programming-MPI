#include "mpi.h"
#include "string.h"
#include "stdio.h"
int main(int argc, char *argv[])
{
	int size , rank , i;
	int *msg;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);

	msg = (char *) malloc(30 * sizeof(char));
	strcpy(msg , "parallel");
	if(rank == 0){
		printf("Hello rank 0 send %s\n", msg);
	}
	MPI_Bcast(msg , 30 , MPI_CHAR , 0 , MPI_COMM_WORLD);
	if(rank != 0){
		printf("rank %d << %s", rank , msg);
	}
	MPI_Finalize();
	return 0;
}