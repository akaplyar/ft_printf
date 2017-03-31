cmake_minimum_required(VERSION 3.6)
project(ft_printf)

set(${CMAKE_C_FLAGS} "-Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES ft_printf.c ft_printf.h finder.c checker.c parse_int.c
        ft_llitoa.c help_int.c main.c parse_str.c type_finder.c main.c.c parse_wstr.c parse_brackets.c)
add_executable(ft_printf ${SOURCE_FILES})
target_link_libraries(ft_printf ${CMAKE_SOURCE_DIR}/libft/libft.a)