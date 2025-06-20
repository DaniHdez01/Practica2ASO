#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cliente.h"

Cliente crearCliente(int n, int prioridad) {
    Cliente nuevoCliente;
    nuevoCliente.nCliente = n;
    nuevoCliente.estado = COLA; // Inicialmente en cola
    nuevoCliente.prioritario = prioridad; // No prioritario por defecto
    return nuevoCliente;
}
void dormirCliente(Cliente *cliente) {
    int tiempoEspera = rand() % 6 + 5; // Genera un número entre 5 y 10
    printf("Cliente n: %d siendo atendido por %d segundos\n", cliente->nCliente, tiempoEspera);
    sleep(tiempoEspera); // Duerme por el tiempo especificado
    printf("Cliente n: %d ha terminado de ser atendido\n", cliente->nCliente);
}

void atenderCliente(Cliente *cliente, Caja *caja){
    if (cliente.prioritario == 0){
        cliente.estado = ATENDIENDO; 
        printf("El cliente %d esta siendo atendido en la caja %d", cliente.nCliente, caja.nCaja); 
        sleep(500); 
    } else {
        cliente.estado = ATENDIENDO; 
        printf("El cliente %d esta siendo atendido en la caja %d", cliente.nCliente, caja.nCaja); 
        sleep(1000); //Si el cliente es prioritario se le atiende más tiempo y en una caja prioritario 
    }
}