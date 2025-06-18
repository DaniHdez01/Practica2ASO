#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[]){

    int hayClientes = 1;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if(rank == 0){ // Proceso padre -> Distribuye clientes a las cajas

        int clientes = 20;//NUmero de clientes en cola 
        int cajas = 10; //NUmero de cajas inicialmente abierto

        MPI_Request * estadoNodos = (MPI_Request *)malloc(sizeof(MPI_Request)*size);

        for (int i = 0; i < size; i++){
            //Pasamos un cliente al proceso esclavo
            MPI_Send(&hayClientes, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            //Quitamos un cliente de la cola 
            clientes--;
            //Comprobamos los clientes en cola y las cajas 

            if(clientes == cajas){ //Si clientes = colas, cerramos una caja
                cajas--; 
            } else if(cajas == clientes/2){ //Si los clienets son elo doble, abrimos una caja
                cajas++; 
            }

        }


        while(1){

            MPI_Status status;
            int terminado;

            MPI_Recv(&terminado, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

            if(clientes <= 0){
                hayClientes = 0;
                MPI_Send(&hayClientes, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);

            }else{
                MPI_Send(&hayClientes, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                clientes--;
            }

            if(clientes <= 0){
                int procesos_finalizados = 0;
                for(int i = 1; i < size; i++){
                    MPI_Recv(&terminado, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
                    hayClientes = 0;
                    MPI_Send(&hayClientes, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                    procesos_finalizados++;
                }

                break;

            }

        }

        free(estadoNodos);

    }else{
        while(1){
            MPI_Recv(&hayClientes, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if(!hayClientes) break;

            printf("Proceso %d atendiendo cliente...\n", rank);
            sleep(2);

            int terminado = 1;
            MPI_Send(&terminado, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}