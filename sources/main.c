/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/12 09:27:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

int		check_map(int fd)
{
		/*
		   char	buf[1000001];
		   int		ret;

		   ret = 0;
		   if (fd == -1)
		   return (0);
		   if ((ret = read(fd, buf, 1000000)))
		   buf[ret] = '\0';
		   if (buf[ret - 1] != '\n')
		   return (0);
		   if (buf[ret - 1] == '\n' && buf[ret - 2] == '\n')
		   return (0);
		   return (1);
		 */
		return (fd);
}

int		main(int ac, char **av)
{
		int		fd;
		int		**map;
		int		size_x;
		int		size_y;

		if (ac == 2)
				fd = open(av[1], O_RDONLY);
		else
				fd = open("maps/42.fdf", O_RDONLY);
		if (fd > 0)
				if ((map = get_the_map(fd, &size_x, &size_y)))
						env(map, size_x, size_y);
		return (0);
}
