#include "cuda_test.cuh"
#include <iostream>

int main(){
    std::cout << "Hola mundo desde la CPU!" << std::endl;

    // Llamamos a una función escrita en código CUDA
    ejecutar_codigo_cuda();
}
