# Declarar ejecutable
# https://cmake.org/cmake/help/latest/command/add_executable.html
add_executable(openmp_example
    main.cpp
)

# Enlazar el ejecutable con las librería de OpenMP
# https://cmake.org/cmake/help/latest/command/target_link_libraries.html
target_link_libraries(openmp_example PRIVATE OpenMP::OpenMP_CXX)
