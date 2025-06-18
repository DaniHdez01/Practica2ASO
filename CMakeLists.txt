cmake_minimum_required(VERSION 3.10)
project(MiProyectoC VERSION 1.0 LANGUAGES C)

# Estándar de C (opcional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Buscar MPI
find_package(MPI COMPONENTS C REQUIRED )

# Crear ejecutable
add_executable(mi_programa  src/Cliente.c src/cola.c)

target_link_libraries(mi_programa PRIVATE MPI::MPI_C)

# Incluir la carpeta de headers
target_include_directories(mi_programa PRIVATE include)
