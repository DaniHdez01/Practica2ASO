#ifndef CAJA_H
#define CAJA_H

#include <stdio.h>


enum ESTADOCAJA{
    ABIERTA, 
    CERRADA,
}; 

typedef struct{
    enum ESTADOCAJA estado; 
    int prioritaria;  // 1=true 0=false 
}Caja; 

Caja cajaNueva(); 
void abrirCaja(); 
void cerrarCaja(); 

#endif