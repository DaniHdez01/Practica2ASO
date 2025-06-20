#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cliente.h"
#include "Caja.h"

//APARTADO A: Cola de clientes y cajas simple, sin prioridad


int main (int argc, char * argv[]){

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype ClienteData; //Datatype para enviar clientes

    Cliente colaClientes[100]; //cola de los clientes
    Caja cajasAbiertas[100];  //cajas abiertas

    int clientesEnCola = 0; 
    int cajasOperativas= 0; 

    //Pedir al usuario que indique el número de clientes
    printf("Indica con cuantos clientes deseas operar"); 
    scanf("%d", &clientesEnCola); 

    //Imprimimos un mensaje de error para que no se pueda poner mas de 100 clientes
    if(clientesEnCola>100){
        printf("ERROR: el numero de clientes debe ser menor que 100"); 
        return 1; 
    } 

    cajasOperativas = clientesEnCola /2; //Las cajas deben ser la mitad que los clientes 

    //Iniciar los clientes 
    for(int i =0; i<clientesEnCola; i++){
        Cliente nuevo = crearCliente(i, 0); //Como no hay que tener en cuenta la prioridad la iniciamos todas a 0 
        colaClientes[i] = nuevo; 
    }

    //Iniciar las cajas
    for(int i = 0; i<cajasOperativas; i++){
        //EStablecemos un numero de cajas nuevas que sean la mitad de los clientes que hay en cola 
        Caja nueva = cajaNueva(i, 0); 
        nueva.estado = ABIERTA;
        cajasAbiertas[i] = nueva; 
    }

    if(rank == 0){ // Proceso padre -> Distribuye clientes a las cajas

        int clienteActual = 0; //Contador de clientes

        //Minetras haya clientes en cola 
        while(clientesEnCola>0){
            for (int i = 0; i < size; i++){
                //Pasamos un cliente al proceso esclavo
                Cliente act = colaClientes[clienteActual]; 
                printf("Turno del cliente: %d", act.nCliente); 
                MPI_Send(&act, 1, ClienteData, i, 1, MPI_COMM_WORLD);  

                //Quitamos un cliente de la cola 
                clientesEnCola--; 

                //Comprobamos los clientes en cola y las cajas 

                if(clientesEnCola == cajasOperativas){
                    cajasAbiertas[cajasOperativas].estado = CERRADA;  //Si clientes = colas, cerramos una caja
                    cajasOperativas--; 
                } else if(cajasOperativas == clientesEnCola/2){ //Si los clienets son el doble, abrimos una caja
                    cajasOperativas++; 
                    Caja nuevaCaja = cajaNueva(cajasOperativas, 0); 
                }

            }
            //Actualizamos el indice en el que se encuentra el padre 
            clienteActual= (clienteActual +1) %clientesEnCola; 
    }
    } else{
        Cliente recibido; 
        MPI_Recv(&recibido, 1, ClienteData, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        //Recibe el cliente que el padre le manda 
        Caja actual; 
        //Busca una caja que esté abierta 
        for(int i=0; i<cajasOperativas; i++){
            if(cajasAbiertas[i].estado == ABIERTA){
                cajasAbiertas[i].estado = ATENDIENDO; 
                actual = cajasAbiertas[i];  
            }
        }
        //Procesa al cliente 
        atenderCliente(&recibido, &actual); 
        //El cliente pasa a estar dormido
        dormirCliente(actual);  

        //Una vez atendido el cliente la caja vuelve a estar abierta
        printf("Cliente n: %d ya ha sido atendido, vuelve a la cola", recibido.nCliente); 
        actual.estado = ABIERTA;

        //Manda al cliente a la cola 
        clientesEnCola++; 
        colaClientes[clientesEnCola] = recibido; 

    }

    MPI_Finalize();
    return 0;
}