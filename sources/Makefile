# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2016/11/11 20:25:13 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	../fdf
SRC		= 	main.c \
			mlx_env.c \
			print_somthing.c \
			hook.c \
			hook_2.c \
			hook_3.c \
			hook_cam.c \
		 	drawline.c \
			draw_line_triangle.c \
			draw_link_face.c \
			map_adapt_to_cam.c \
			maped.c \
			print_map.c \
			print_map_end.c \
			cam.c \
			exit.c \
			its_parse_time.c \
			its_parse_time_2.c 

OBJ		= $(SRC:.c=.o)

LIB_DIR		= -L ../libft -L ../c_maths
LIB_NAME	=  -lmlx -lc_maths -lft -lm  #-lX11 -lXext

# //////////////// cross platforme
OS	:=	$(shell uname -s)
PROC	:= $(shell uname -p)

ifeq "$(OS)"	"Linux"
  LIB_DIR	+=  -L ../minilibx
  LIB_NAME	+=  -lX11 -lXext
  FRAMEWORK	= 
else ifeq "$(OS)" "Darwin"
  FRAMEWORK	= -framework OpenGl -framework AppKit
  LIB_DIR	+=  -L ../minilibx_macos
endif

# ////////////////



FLAGS = -Wall -Wextra -Werror -Ofast
FLAGS-DEBUG = -g -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJ)
ifeq "$(OS)" "Darwin"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(LIB_NAME) $(OBJ)
else ifeq "$(OS)" "Linux"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(OBJ) $(LIB_NAME)
endif


$(OBJ):
	gcc -c $(FLAGS) $(SRC) -I ../includes -I ../c_maths# -I /usr/includes/
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all

gdb: fclean
		gcc -c $(FLAGS-DEBUG) $(SRC) -I ../includes -I ../c_maths# -I /usr/includes/
		gcc -o $(NAME) $(FLAGS-DEBUG) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-L /usr/lib/ -lmlx -lm -lX11 -lXext
