#include "Cliente.h"
#include "Caja.h"
#include <stdio.h>

Caja cajaNueva(int id, int prioridad){
    Caja nueva; 
    nueva.nCaja = id; 
    nueva.estado = CERRADA; 
    nueva.prioritaria = prioridad; 
    nueva.clienteAtendido = NULL; 
}

