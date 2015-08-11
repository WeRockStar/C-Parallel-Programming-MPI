#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
int main(int argc, char *argv[])
{
	int size , rank;
	long num1,num2;
	int *send;
	MPI_Init(&argc , &argv);
	MPI_Status status;
	MPI_Request resquest[2];	
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);		
	send = (int *)malloc(2 * sizeof(int));
	if(rank == 0){	       
		scanf("%ld %ld" , &num1 , &num2);
		MPI_Send(&num1 , 10 , MPI_LONG , 1 , 1 , MPI_COMM_WORLD);
		MPI_Send(&num2 , 10 , MPI_LONG , 1 , 2 , MPI_COMM_WORLD);
		MPI_Send(&num1 , 10 , MPI_LONG , 2 , 1 , MPI_COMM_WORLD);
		MPI_Send(&num2 , 10 , MPI_LONG , 2 , 2 , MPI_COMM_WORLD);
		MPI_Send(&num1 , 10 , MPI_LONG , 3 , 1 , MPI_COMM_WORLD);
		MPI_Send(&num2 , 10 , MPI_LONG , 3 , 2 , MPI_COMM_WORLD);
	}else if(rank == 1){ 
		MPI_Irecv(&num1 , 10 , MPI_LONG , 0 , 1 , MPI_COMM_WORLD , &resquest[0]);
		MPI_Irecv(&num2 , 10 , MPI_LONG , 0 , 2 , MPI_COMM_WORLD , &resquest[1]);
		MPI_Wait(&resquest[0] , &status);
		MPI_Wait(&resquest[1] , &status);
		//C1	
		printf("al : %d\n", getLeft(num1 , num2));
		long c1 = getLeft(num1 , num2) * getLeft(num2 , num1);
		//printf("rank1 c1 : %d\n", c1);
	}else if(rank == 2){ //C2
		MPI_Irecv(&num1 , 10 , MPI_LONG , 0 , 1 , MPI_COMM_WORLD , &resquest[0]);
		MPI_Irecv(&num2 , 10 , MPI_LONG , 0 , 2 , MPI_COMM_WORLD , &resquest[1]);
		MPI_Wait(&resquest[0] , &status);
		MPI_Wait(&resquest[1] , &status);
		//C2		
		long c2 = getRight(num1 , num2) * getRight(num2 , num2);
		//printf("rank2 c2 : %d\n", c2);
		MPI_Send(&c2 , 10 , MPI_LONG , 3 , 1 , MPI_COMM_WORLD);
		
	}else if(rank == 3){ //C3	
		MPI_Irecv(&num1 , 10 , MPI_LONG , 0 , 1 , MPI_COMM_WORLD , &resquest[0]);
		MPI_Irecv(&num2 , 10 , MPI_LONG , 0 , 2 , MPI_COMM_WORLD , &resquest[1]);
		MPI_Wait(&resquest[0] , &status);
		MPI_Wait(&resquest[1] , &status);		
		//printf("rank3 c3 : %d\n", num1);
		
	}
	MPI_Finalize();
	return 0;
}

int getLeft(int num1 , int num2){	
	int left = getRight(num1 , num2);	
	left = (num1 - left); 
	return left;
}
int getRight(int num1 , int num2){
	int n = getMaxN(num1 , num2);
	int right = (num1 % (int)(pow(10 , n)));
	return right;
}
int getMaxN(long num1 , long num2){
	int size1 = getSize(num1);
	//printf("Size : %d\n" , size1);
	int size2 = getSize(num2);
	int n = size1 >= size2 ? size1 : size2;
	n = (n / 2) + (n % 2);	
	return n;
}
int getSize(long n){
	int count = 0;
	while(n != 0){
		count++;
		n/=10;
	}
	return count;
}