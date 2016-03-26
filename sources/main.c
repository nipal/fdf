/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/26 17:39:46 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"


int		main(int ac, char **av)
{
	int		fd;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("maps/42.fdf", O_RDONLY);
	if (fd > 0)
	{
		if (check_map(fd))
		{
			close(fd);
			if (ac == 2)
				fd = open(av[1], O_RDONLY);
			else
				fd = open("maps/42.fdf", O_RDONLY);
			if (fd > 0)
				env(fd);
		}
		else
			ft_putendl_fd("No \\n or more than 2 \\n at the end of file", 2);
	}
	return (0);
}
