# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 16:36:05 by akaplyar          #+#    #+#              #
#    Updated: 2017/03/29 14:53:34 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft/

MAKE_LIB = $(MAKE) -C ${LIB_PATH}

OBJ = ft_printf.o help_int.o parse_int.o parse_str.o finder.o type_finder.o

HEADER = ft_printf.h

TARGET = libprintf.a

.PHONY: clean fclean re ft

all: ft $(OBJ) $(TARGET)

$(TARGET):
	ar rcs $(TARGET) $(OBJ) $(HEADER)
	ranlib $(TARGET)

ft:
	$(MAKE_LIB)

clean:
	rm -rf $(OBJ)
	$(MAKE_LIB) clean

fclean: clean
	rm -rf $(TARGET)
	$(MAKE_LIB) fclean

re: fclean all
