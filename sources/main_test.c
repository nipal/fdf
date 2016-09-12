/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 23:30:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/12 09:08:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>



#include <stdio.h>
#include "libft.h"


t_list	*read_line_number(int fd);

int	main(int ac, char **av)
{
	int		fd;
	int		j;
	t_list	*elem;
	t_list	*begin;
	int		x_max;
	int		y_max;
	int		**map;

	j = 1;
	if (ac <= 1)
		return (1);
	while (j < ac)
	{
		if ((fd = open(av[j], O_RDONLY)) < 0)
			return (2);
		dprintf(1, "\n\n\nname file:	{%s}\n", av[j]);
					//dprintf(1, "avant\n");
		while ((elem = read_line_number(fd)))
		{
//			print_elem(elem);
			elem->next = begin;
			begin = elem;
//		dprintf(1, "-----------------------------------------------\n");
//			print_all(begin);
//		dprintf(1, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
		}
//		print_all(begin);
		if (!(map = get_map(begin, &x_max, &y_max)))	
			dprintf(1, "Error on getting the map");
		dprintf(1, "-----------------------------------------------\n");
		print_map(map, x_max, y_max);
		close(fd);
//	dprintf(1, "apres\n");
		j++;
	}
	return (0);
}

/*
 *	On veux juste envoyer un fd  et yolooo
 *
 * */
