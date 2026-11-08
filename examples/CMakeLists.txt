cmake_minimum_required(VERSION 3.20)
project(nozzle_c_reference LANGUAGES C CXX)

find_package(nozzle CONFIG REQUIRED)
add_executable(c_reference ../_includes/examples/c_reference.c)
set_target_properties(c_reference PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
)
target_link_libraries(c_reference PRIVATE nozzle::nozzle)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(c_reference PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
