# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2016/10/03 17:40:18 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export FLAGS	= -Wall -Wextra -Werror
NAME			= fdf
SRC_DIR			= ./sources
LIB_FT			= ./libft
LIB_M			= ./c_maths

# //////////////// cross platforme
OS	:=	$(shell uname -s)
PROC	:= $(shell uname -p)
# ////////////////

ifeq "$(OS)" "Windows_NT"
exit # sorry but not sorry =)
else ifeq "$(OS)" "Linux"
LIB_MLX			= ./minilibx
else ifeq "$(OS)" "Darwin"
LIB_MLX			= ./minilibx_macos
endif



all:
	make -C $(LIB_MLX)
	make -C $(LIB_FT)
	make -C $(LIB_M)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_FT)  clean
	make -C $(LIB_M)  clean
	make -C $(SRC_DIR) clean

fclean: clean
	make -C $(LIB_FT)  fclean
	make -C $(LIB_M)  fclean
	make -C $(SRC_DIR) fclean

re: fclean all

gdb:
	make -C $(LIB_FT) gdb
	make -C $(LIB_M) gdb
	make -C $(SRC_DIR) gdb
