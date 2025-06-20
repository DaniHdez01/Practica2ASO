#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cliente.h"
#include "Caja.h"

//APARTADO B: Cola de clientes prioritariuos y cajas normales


int main (int argc, char * argv[]){

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Datatype ClienteData; //Datatype para enviar clientes

    Cliente colaClientes[100];
    Cliente colaPrioritaria[10]; //Guardamos a los clientes prioritarios en una cola a parte 
    Caja cajasAbiertas[100];  

    int clientesEnCola = 0; 
    int cajasOperativas= 0; 
    int clientesVIP = 0; //Son los clientes prioritarios 

    printf("Indica con cuantos clientes deseas operar"); 
    scanf("%d", &clientesEnCola);

    //Imprimimos un mensaje de error para que no se pueda poner mas de 100 clientes
    if(clientesEnCola>100){
        printf("ERROR: el numero de clientes debe ser menor que 100"); 
        return 1; 
    } 
    printf("Indica con cuantos clientes deseas operar"); 
    scanf("%d", &clientesVIP);
    clientesEnCola += clientesVIP; 
    for(int i =0; i<clientesEnCola; i++){
        Cliente nuevo = crearCliente(i, 0); //Los clientes prioritarios ahora se generan de forma aleatoria 
        colaClientes[i] = nuevo; 
    }
    for(int i =0; i<clientesVIP; i++){
        Cliente newVIP = crearCliente(i+clientesEnCola, 1);  // El id sumamos i a los clientes totales para que tengan un id distinto al resto
        colaPrioritaria[i] = colaPrioritaria[i]; 
    }
    for(int i = 0; i<cajasOperativas; i++){
        //EStablecemos un numero de cajas nuevas que sean la mitad de los clientes que hay en cola 
        Caja nueva = cajaNueva(i, 0); 
        nueva.estado = ABIERTA;
        cajasAbiertas[i] = nueva; 
    }

    if(rank == 0){ // Proceso padre -> Selecciona los clientes de la cola y los manda al proceso hijo. 

        int clienteActual = 0; 
        int vipActual = 0; 
        //Ahora el padre mirará primero en la cola de clientes prioritarios hasta que esté vacia, una vez hecho mirará en la cola normal 
        while(clientesEnCola>0){
            while (clientesVIP >0){
                for (int i = 0; i < size; i++){
                    //Pasamos un cliente al proceso esclavo
                    Cliente VIPact = colaClientes[clienteActual]; 
                    printf("Turno del cliente: %d", VIPact.nCliente); 
                    MPI_Send(&VIPact, 1, ClienteData, i, 1, MPI_COMM_WORLD);  
    
                    //Quitamos un cliente de la cola 
                    clientesVIP--; 
    
                    //Comprobamos los clientes en cola y las cajas 
    
                    if(clientesEnCola == cajasOperativas){ //Si clientes = colas, cerramos una caja
                        cajasOperativas--; 
                    } else if(cajasOperativas == clientesEnCola/2){ //Si los clienets son elo doble, abrimos una caja
                        cajasOperativas++; 
                    }
    
                }
                vipActual = (vipActual +1) % clientesVIP; 
            }

            //Procesamos las colas normales una vez la VIP esté vacia 
            for (int i = 0; i < size; i++){
                //Pasamos un cliente al proceso esclavo
                Cliente act = colaClientes[clienteActual]; 
                printf("Turno del cliente: %d", act.nCliente); 
                MPI_Send(&act, 1, ClienteData, i, 1, MPI_COMM_WORLD);  

                //Quitamos un cliente de la cola 
                clientesEnCola--; 

                //Comprobamos los clientes en cola y las cajas 

                if(clientesEnCola == cajasOperativas){
                    cajasAbiertas[cajasOperativas].estado = CERRADA;//Si clientes = colas, cerramos una caja
                    cajasOperativas--; 
                } else if(cajasOperativas == clientesEnCola/2){ //Si los clienets son elo doble, abrimos una caja
                    cajasOperativas++; 
                    Caja nuevaCaja = cajaNueva(cajasOperativas, 0); 
                }

            }
            //Actualizamos el indice en el que se encuentra el padre 
            clienteActual= (clienteActual +1) %clientesEnCola; 
    }
    } else{ //Proceso hijo, recibe los clientes y le asigna la caja correspondiente
        Cliente recibido; 
        MPI_Recv(&recibido, 1, ClienteData, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        Caja actual; 
        for(int i=0; i<cajasOperativas; i++){
            if(cajasAbiertas[i].estado == ABIERTA){
                cajasAbiertas[i].estado = ATENDIENDO; 
                actual = cajasAbiertas[i];  
            }
        }
        atenderCliente(&recibido, &actual); 
        dormirCliente(actual);  
        printf("Cliente n: %d ya ha sido atendido, vuelve a la cola", recibido.nCliente); 
        actual.estado = ABIERTA;

        clientesEnCola++; 
        colaClientes[clientesEnCola] = recibido; 
        //Hemos decidido que lso clientes prioritarios vuelven a la cola normal
    }

    MPI_Finalize();
    return 0;
}