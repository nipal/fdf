# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by jpirsch           #+#    #+#              #
#    Updated: 2016/03/12 11:30:56 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export FLAGS	= -Wall -Wextra -Werror
NAME			= fdf
SRC_DIR			= ./sources
LIB_DIR			= ./libft

all:
	make -C $(LIB_DIR)
	make -C $(SRC_DIR)

clean:
	make -C $(LIB_DIR) clean
	make -C $(SRC_DIR) clean

fclean: clean
	make -C $(LIB_DIR) fclean
	make -C $(SRC_DIR) fclean

re: fclean all
