# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by jpirsch           #+#    #+#              #
#    Updated: 2016/09/12 09:18:58 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../fdf
SRC		= 	main.c \
	 		parse.c \
			mlx_env.c \
			hook.c \
		 	drawline.c \
			maped.c \
			print_map.c \
			its_parse_time.c \
			cam.c 
#			coord.c
OBJ		= $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L ../libft/ -lft -L ../minilibx/ \
		-L ../c_maths -lc_maths \
		-lmlx -framework OpenGL -framework AppKit

$(OBJ):
	gcc -c  $(FLAGS) $(SRC) -I ../includes -I ../c_maths

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
