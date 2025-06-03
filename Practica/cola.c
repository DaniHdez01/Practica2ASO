#include "mpi.h"
#include <stdio.h>

int main (int argc, char * argv[]){

    int rank, size;
    MPI_Init();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int cajas = 0;
    int clientesCola = 0;

    if(rank == 0){

    }

    
}