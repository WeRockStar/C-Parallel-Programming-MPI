#include "mpi.h"
int main(int argc , char *argv[]){
	int rank , size;
	int i;
	char *msg;
	MPI_Status status;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Init(&argc , &argc);
	MPI_Comm_size(comm , &size);
	MPI_Comm_rank(comm , &rank);
	msg = (int *)malloc(25 * sizeof(char));

	if(rank == 0){
		for(i = 1;i<size;i++){
			MPI_Recv(msg , 25 , MPI_CHAR , i , 0 , comm , &status); //message , count , datatype , dest , tag , comm , status
			printf("%s\n", msg);
		}
	}else{
		sprintf(msg , "Hello World form rank : %d" , rank);
		MPI_Send(msg , 25 , MPI_CHAR , i , 0 , comm);
	}

	MPI_Finalize();
}