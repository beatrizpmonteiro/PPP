cmake_minimum_required(VERSION 3.21)
project(projeto C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)

add_executable(projeto base.c auxproj.c header_projeto.h)





