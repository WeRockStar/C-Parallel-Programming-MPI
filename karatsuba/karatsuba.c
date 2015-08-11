#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
int main(int argc, char *argv[])
{
    int size , rank;
    MPI_Init(&argc , &argv);
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Request resquest[2];    
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);          
    srandom(rank);
    long a = 12, b = 555551 , mid , c1 , c2 , c3 , start , end; 
    if(rank == 0){
        start = MPI_Wtime();
        c1 = getC1(a, b);
        c2 = getC2(a , b); 
        c3 = getC3(a , b);  
        MPI_Send(&c1 , 10 , MPI_LONG , 1 , 1 , MPI_COMM_WORLD);
        MPI_Send(&c2 , 10 , MPI_LONG , 1 , 2 , MPI_COMM_WORLD);
        MPI_Send(&c3 , 10 , MPI_LONG , 1 , 3 , MPI_COMM_WORLD);     
    }else if(rank == 1){
        MPI_Recv(&c1 , 10 , MPI_LONG , 0 , 1 , MPI_COMM_WORLD , &status);
        MPI_Recv(&c2 , 10 , MPI_LONG , 0 , 2 , MPI_COMM_WORLD , &status);
        MPI_Recv(&c3 , 10 , MPI_LONG , 0 , 3 , MPI_COMM_WORLD , &status);
        long sum = (c1*pow(10 , getCount(a))) + ((c3- c1 - c2) * pow(10 , getCount(a)/2)) + c2;
        end = MPI_Wtime();
        //printf("a x b : %d , Time : %1.4f\n",sum, (end - start));
        printf("%d x %d : %d\n", a , b , sum);

    }    
    MPI_Finalize();
    return 0;
}
int getC1(long i ,long j){
    if (i < 10 || j < 10){
        return (int)i * j;
    }
    int n = getCount(i);
    long a = (long) (i / (int)pow(10, n / 2));    
    long c = (long) (j / (int)pow(10, n / 2));    
    long c1 = getC1(a, c);
    return c1;
}
int getC2(long i ,long j){
    if (i < 10 || j < 10){
        return (int)i * j;
    }
    int n = getCount(i);    
    long b = (long) (i % (int)pow(10, n / 2));    
    long d = (long) (j % (int)pow(10, n / 2));
    long c2 = getC2(b, d);
    return c2;
}
int getC3(long i ,long j){
    if (i < 10 || j < 10){
        return (int)i * j;
    }
    int n = getCount(i);
    long a = (long) (i / (int)pow(10, n / 2));
    long b = (long) (i % (int)pow(10, n / 2));
    long c = (long) (j / (int)pow(10, n / 2));
    long d = (long) (j % (int)pow(10, n / 2));
    long c3 = getC3(a + b, c + d);
    return c3;
}

int getCount(long i)
{
    int count = 0;
    while(i != 0){
        count++;
        i/=10;
    }
    return count;
}
