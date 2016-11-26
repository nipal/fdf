/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/23 10:35:28 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

char	*maps_name(char *str)
{
	static	char	*name = NULL;

	if (str)
		name = str;
	return (name);
}

int		main(int ac, char **av)
{
	int		fd;
	int		**map;
	int		size_x;
	int		size_y;

	if (ac != 2)
	{
		ft_putstr("usage:	./fdf FDF_FILE\n");
		return (1);
	}
	maps_name(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd > 0)
	{
		if ((map = get_the_map(fd, &size_x, &size_y)))
			env(map, size_x, size_y, av[1]);
	}
	else
		perror(av[1]);
	return (0);
}
