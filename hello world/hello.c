#include <mpi.h>
#include <stdio.h>
int int main(int argc, char *argv[])
{
	MPI_Init(&argc , &argv);
	int size , rank;
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	//rank = id process , size = size of process
	printf("Hello World from rank : %d of %d\n", rank , size);
	
	MPI_Finalize();
	return 0;
}