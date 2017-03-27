cmake_minimum_required(VERSION 3.6)
project(ft_printf)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES ft_printf.c ft_printf.h finder.c checker.c)
add_library(ft_printf ${SOURCE_FILES})