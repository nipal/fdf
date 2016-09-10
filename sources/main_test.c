/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 23:30:52 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/10 07:31:15 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>



#include <stdio.h>
#include "libft.h"


t_list	*read_line_number(int fd);
void	print_elem(t_list *elem)
{
	int	i;
	int	**tmp;
	int	*tab;
	int	max;

	i = 0;
	if (!(elem))
		return ;
//	tmp = (((int**) elem->content));
	tab = elem->content;
	max = elem->content_size;
//	*dprintf(1, "size:	[%d]\n", max);
//	*dprintf(1, "adrr:	[%ld]\n", (long)tab);
//	*dprintf(1, "line_number:	\n");
	//i = *tab;
	i = 0;
//	*dprintf(1, "ouiiii	");
	if (tab)
	{
//	*dprintf(1, "\n\naie aie aie\n\n\n");
	}
//	*dprintf(1, "max:%d	i:%d\n", max, i);
//	*dprintf(1, "encor un peu\n");
	while (i < max)
	{
//	*dprintf(1, "et puis la\n");
		dprintf(1, " (%d)", tab[i]);
		i++;
	}
	dprintf(1, "\n");
}

int	main(int ac, char **av)
{
	int		fd;
	int		i;
	int		j;
	t_list	*elem;

	i = 0;
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
			print_elem(elem);

		}
		close(fd);
//	dprintf(1, "apres\n");
		j++;
	}
	return (0);
}
