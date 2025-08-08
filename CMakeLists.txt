cmake_minimum_required(VERSION 3.10)
project(name_mangling)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

# Output object file
set_target_properties(main PROPERTIES
    COMPILE_PDB_NAME main
    COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)