# Declarar ejecutable
# https://cmake.org/cmake/help/latest/command/add_executable.html
add_executable(mpi_example
    main.cpp
)

# Enlazar el ejecutable con las librería de MPI
# https://cmake.org/cmake/help/latest/command/target_link_libraries.html
target_link_libraries(mpi_example PRIVATE MPI::MPI_CXX)
