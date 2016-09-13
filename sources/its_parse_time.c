/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/13 04:29:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 *	On lis ligne par ligne
 *	On va changer tout les ['	', '\r', '\t'] etc en espace : ' '
 *	On split sur les espace et on stoque dans des maillon
 *	
 *	On connait les dimmantion de la map
 *	On malloc la map a la bonne taille 
 *	
 *	On fait le atoi modifier pour aussi choper les couleur de le map
 * */

/*
 *	
 *
 * */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

void	ft_replace(char *str, char *to_find, char replace)
{
	int	i;

	i = 0;
	if (!str || !to_find)
		return ;
	while (str[i])
	{
		if (ft_strrchr(to_find, str[i]) != 0)
			str[i] = replace;
		i++;
	}
}

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}



int		*get_number_from_str(char **char_nb,int *size)
{
	int	*tab_nb;
	int	i;

	i = 0;
	//	dprintf(1, "before get_number_from_str\n");
	if (!char_nb || !*char_nb)
		return (NULL);
	if (!size)
		return (NULL);
	*size = ft_tablen(char_nb);
	if (*size <= 0 || !(tab_nb = (int*)malloc(*size * sizeof(int))))
		return (NULL);	

	//	dprintf(1, "size:%d\n", *size);
	while (i < *size)
	{
		tab_nb[i] = ft_atoi(char_nb[i]);
//		dprintf(1, " <%s, %d>", char_nb[i], tab_nb[i]);		
		if (is_int_over_flow(char_nb[i]))
		{
//			dprintf(1, "ther is a problem for {%s}\n", char_nb[i]);
			tab_nb[i] = -42;
		}
		else
		{
			tab_nb[i] = atoi(char_nb[i]);
		}
		i++;
	}
	//	dprintf(1, "\n");
	//	dprintf(1, "after get_numbert_from_str\n");
	return (tab_nb);
}

void	print_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		dprintf(1, "	str[%d]	:%s:	", i, tab[i]);
		i++;
	}
	dprintf(1, "\n");
}

void	print_int_tab(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dprintf(1, " 	%d", tab[i]);
		i++;
	}
}

t_list	*read_line_number(int fd)
{
	char	**tab_nb;
	char	*line;
	int		ret;
	int		*line_nb;
	t_list	*elem;

	//	dprintf(1, "begin\n");
	ret = get_next_line(fd, &line);
	//	dprintf(1, "ret:::	%d\n", ret);
	if (ret <= 0)
		return (NULL);
	//	dprintf(1, "line	get_next	[%s]\n", line);
	ft_replace(line, "\t\v\r", ' ');	
	//	dprintf(1, "line	replace		[%s]\n", line);
	tab_nb = ft_strsplit(line, ' ');
	//	dprintf(1, "affter split\n");
//	print_char_tab(tab_nb);
	if (!(line_nb = get_number_from_str(tab_nb, &ret)))
		return (NULL);
//	print_int_tab(line_nb, 10);
	//	dprintf(1, "ret:	((%d))\n", ret);
	if (!(elem = ft_lstnew(line_nb, ret * sizeof(int))))
		return (NULL);
	//	dprintf(1, "ending\n");
	return (elem);
}

void	get_size(t_list *begin, int *max_x, int *max_y)
{
	int		x_max;
	int		y_max;
	t_list	*elem;


	x_max = 0;
	y_max = 0;
	elem = begin;
	while (elem)
	{
		if ((int)(elem->content_size / sizeof(int)) > x_max)
			x_max = elem->content_size / sizeof(int);
		elem = elem->next;
		y_max++;
	}
	*max_x = x_max;
	*max_y = y_max;;
}

void	print_elem(t_list *elem)
{
	int	i;
	int	*tab;
	int	max;

	i = 0;
	if (!(elem))
		return ;
	tab = (int*)elem->content;
	max = elem->content_size / sizeof(int);
	i = 0;
	if (!tab)
	{
		dprintf(1, "\n\naie aie aie\n\n\n");
		return ;
	}
	dprintf(1, "	|->");
	while (i < max)
	{
		dprintf(1, "	%d", tab[i]);
		i++;
	}
	dprintf(1, " <---{%d}\n", i);
}

void	print_int_map(int **map, int max_x, int max_y)
{
	int	i;
	int	j;

	j = 0;
	while (j < max_y)
	{
		i = 0;
		while (i < max_x)
		{
			dprintf(1, "	%d", map[j][i]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
}

int	**get_map_lst(t_list *begin, int *max_x, int *max_y)
{
	int		*line;
	int		**tab;
	int		i;
	int		j;
	t_list	*elem;

	elem = begin;
	if (!begin || !elem || !max_x || !max_y)
		return (NULL);
	get_size(begin, max_x, max_y);
	if (!(tab = (int **)malloc(sizeof(int*) * *max_y)))
		return (NULL);
	j = *max_y - 1;
	while (j >= 0)
	{
		if (!(tab[j] = (int*)malloc(sizeof(int) * *max_x)))
			return (NULL);
		ft_bzero(tab[j], sizeof(int) * *max_x);
		line = (int*)elem->content;
		i = 0;
		while (i < (int)(elem->content_size / sizeof(int)))
		{
			tab[j][i] = line[i];
			i++;
		}
		elem = elem->next;
		j--;
	}
	return (tab);
}

void	print_all(t_list *begin)
{
	t_list	*elem;

	elem = begin;
	while (elem)
	{
		print_elem(elem);
		elem = elem->next;
	}
}



int	**get_the_map(int fd, int *x_max, int *y_max)
{
	t_list	*elem;
	t_list	*begin;
	int		**map;

	while ((elem = read_line_number(fd)))
	{
		elem->next = begin;
		begin = elem;
	}
	if (!(map = get_map_lst(begin, x_max, y_max)))	
		dprintf(1, "Error on getting the map");
//	print_int_map(map, *x_max, *y_max);
	close(fd);
	return (map);
}
//dprintf(1, "\n");