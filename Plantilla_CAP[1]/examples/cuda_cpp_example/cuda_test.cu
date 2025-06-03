#include <cuda_runtime.h>
#include <stdio.h>

__global__ void saludar_desde_gpu(){
    printf("Hola mundo desde la GPU!\n");
}

void ejecutar_codigo_cuda(){
    // Llamar al código que se ejecuta en la GPU
    saludar_desde_gpu<<<1,1>>>();

    // Esperar a que la GPU acabe de ejecutar el código
    cudaDeviceSynchronize();
}
