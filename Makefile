# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 16:36:05 by akaplyar          #+#    #+#              #
#    Updated: 2017/03/30 15:02:32 by akaplyar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft/

LIB_NAME = $(LIB_PATH)libft.a


vpath %.c $(LIB_PATH)

OBJ = ft_printf.o help_int.o parse_int.o parse_str.o finder.o type_finder.o\
		checker.o parse_wstr.o parse_brackets.o

OBJ2 = ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o\
		ft_memcpy.o ft_memcmp.o ft_memchr.o ft_memmove.o ft_memset.o ft_memccpy.o\
		ft_strcat.o ft_strchr.o ft_strcpy.o ft_strlcat.o ft_strdup.o ft_strlen.o\
		ft_strncpy.o ft_strnstr.o ft_strstr.o ft_strrchr.o ft_strcmp.o\
		ft_strncmp.o ft_toupper.o ft_tolower.o ft_atoi.o ft_strncat.o ft_memalloc.o\
		ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o\
		ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o\
		ft_strtrim.o ft_strsplit.o ft_putchar.o ft_putstr.o ft_putnbr.o ft_putendl.o\
		ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_itoa.o\
		ft_lstnew.o ft_lstadd.o ft_lstmap.o ft_lstiter.o ft_lstdelone.o\
		ft_lstdel.o ft_isspace.o ft_realloc.o ft_abs.o ft_int_sort.o ft_strrev.o\
		ft_lst_push_back.o get_next_line.o ft_lstcount.o ft_strcapitalizer.o\
		ft_atoi_base.o hsv.o hsv_colors.o ft_llitoa.o

FT_OBJ = $(addprefix $(LIB_PATH),$(OBJ2))

P_SRC = $(addprefix $(SRC_DIR),$(OBJ:.o=.c))

HEADER = ft_printf.h

FT_HEADER = $(LIB_PATH)libft.h

NAME = libftprintf.a

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(FT_OBJ) $(OBJ)
	ar rcs $(NAME) $(FT_OBJ) $(OBJ) $(HEADER) $(FT_HEADER)
	ranlib $(NAME)

$(OBJ): $(FT_HEADER) $(HEADER)


$(FT_OBJ): $(FT_HEADER)

clean:
	rm -rf $(OBJ)
	rm -rf $(FT_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
