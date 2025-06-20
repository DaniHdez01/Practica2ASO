#ifndef CLIENTE_H
#define CLIENTE_H
#include <stdio.h>

struct Caja; 

enum ESTADO{
    COLA, 
    ATENDIDO, 
    DORMIDO
}; 

typedef struct{
    int nCliente; //id del cliente 

    enum ESTADO estado; //Donde se encuentra el cliente actualmente

    int prioritario; //1= El cliente es prioritario, por lo tanto será atendido más tiempo en una caja prioritaria 
                    // 0= El cliente no es prioritario, irá a una caja normal 
} Cliente; 

Cliente crearCliente(int n, int prioridad); 

void atenderCliente(Cliente *cliente, struct Caja *caja); 
void dormirCliente(); 
#endif