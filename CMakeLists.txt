cmake_minimum_required(VERSION 3.16)
project(bookish_spoon_sync C)

set(CMAKE_C_STANDARD 11)
link_libraries(pthread)

add_executable(client client.c types.h)
add_executable(server server.c parallelmergesort.c types.h)