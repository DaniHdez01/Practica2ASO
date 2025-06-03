#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <stdio.h>

__global__ void hola_gpu() {
    printf("Hola mundo desde la GPU!\n");
}

int main()
{
    // Saludar desde la CPU
    printf("Hola mundo desde la CPU!\n");

    // Saludar desde la GPU
    hola_gpu<<<1, 1 >>>();

    // Forzar sincronizaci�n con la GPU y esperar a que esta acabe
    // antes de salir del programa
    cudaDeviceSynchronize();
}
