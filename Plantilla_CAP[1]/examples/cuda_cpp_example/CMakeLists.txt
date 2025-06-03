# Declarar ejecutable
# https://cmake.org/cmake/help/latest/command/add_executable.html
add_executable(cuda_cpp_example
    main.cpp
    cuda_test.cu

    # No es necesario añadir archivos de encabezado como archivos
    # de código fuente para que el proyecto funcione, pero suele
    # ayudar para la integración de auto-completado de algunos
    # IDEs como Visual Studio
    cuda_test.cuh
)
