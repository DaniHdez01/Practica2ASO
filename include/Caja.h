#ifndef CAJA_H
#define CAJA_H

#include <stdio.h>
#include "Cliente.h"

enum ESTADOCAJA{
    ABIERTA, 
    CERRADA,
    ATENDIENDO,
}; 

typedef struct Caja{
    int nCaja; 
    enum ESTADOCAJA estado; 
    int prioritaria; 
    Cliente *clienteAtendido; 
}Caja; 

Caja cajaNueva(); 

#endif