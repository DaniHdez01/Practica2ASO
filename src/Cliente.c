#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Cliente.h"

Cliente crearCliente(int n) {
    Cliente nuevoCliente;
    nuevoCliente.nCliente = n;
    nuevoCliente.estado = COLA; // Inicialmente en cola
    nuevoCliente.prioritario = 0; // No prioritario por defecto
    return nuevoCliente;
}
void dormirCliente(Cliente *cliente) {
    int tiempoEspera = rand() % 6 + 5; // Genera un número entre 5 y 10
    printf("Cliente n: %d siendo atendido por %d segundos\n", cliente->nCliente, tiempoEspera);
    sleep(tiempoEspera); // Duerme por el tiempo especificado
    printf("Cliente n: %d ha terminado de ser atendido\n", cliente->nCliente);
}