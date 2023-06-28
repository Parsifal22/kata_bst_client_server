cmake_minimum_required(VERSION 3.10)
project(kata_bst_client_server)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/server)
add_subdirectory(src/client)
add_subdirectory(tests)