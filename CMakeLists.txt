cmake_minimum_required(VERSION 3.10)
project(MiProyectoC VERSION 1.0 LANGUAGES C)

# Estándar de C (opcional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Incluir la carpeta de headers
include_directories(include)

# Buscar MPI
find_package(MPI REQUIRED)

# Crear ejecutable
add_executable(mi_programa src/main.c)

target_include_directories(mi_programa PRIVATE ${MPI_C_INCLUDE_DIRS})
target_link_libraries(mi_programa PRIVATE ${MPI_C_LIBRARIES})
