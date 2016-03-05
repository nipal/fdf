# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/13 19:48:58 by jpirsch           #+#    #+#              #
#    Updated: 2016/03/05 12:51:16 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libc_maths.a
SRC		=	matrix_init.c \
			matrix_display.c \
			matrix_add.c \
			matrix_product.c \
			matrix_scalar_product.c \
			matrix_det.c \
			matrix_inverse.c \
			matrix_transpose.c \
			eq_solve_2nd.c \
			eq_solve_3rd.c \
			eq_solve_4th.c \
			set_rotate.c \
			set_translate.c \
			vector_product.c \
			matrix_copy.c \
			free_mat.c \
			set_scale.c
FLAGS		= -Wall -Wextra -Werror
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:%.c
	gcc -Ofast  -c $(SRC) $(FLAGS) -I ./
#	gcc -Ofast $(FLAGS) -I ../includes/ -c $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
