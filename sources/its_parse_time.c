/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 17:36:45 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

/*
** *	On lis ligne par ligne
** *	On va changer tout les ['	', '\r', '\t'] etc en espace : ' '
** *	On split sur les espace et on stoque dans des maillon
** *	On connait les dimmantion de la map
** *	On malloc la map a la bonne taille
** *	On fait le atoi modifier pour aussi choper les couleur de le map
** *
*/

void		ft_replace(char *str, char *to_find, char replace)
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

int			ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

int			*get_number_from_str(char **char_nb, int *size)
{
	int	*tab_nb;
	int	i;

	i = 0;
	if (!char_nb || !*char_nb)
		return (NULL);
	if (!size)
		return (NULL);
	*size = ft_tablen(char_nb);
	if (*size <= 0 || !(tab_nb = (int*)malloc(*size * sizeof(int))))
		return (NULL);
	while (i < *size)
	{
		tab_nb[i] = ft_atoi(char_nb[i]);
		if (is_int_over_flow(char_nb[i]))
		{
			tab_nb[i] = -42;
		}
		else
		{
			tab_nb[i] = atoi(char_nb[i]);
		}
		i++;
	}
	return (tab_nb);
}

int			free_char_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

int		free_tricks(char *str)
{
	free(str);
	return (1);
}

t_list		*read_line_number(int fd)
{
	char	**tab_nb;
	char	*line;
	int		ret;
	int		*line_nb;
	t_list	*elem;

	ret = get_next_line(fd, &line);
	if (ret <= 0)
		return (NULL);
	ft_replace(line, "\t\v\r", ' ');
	tab_nb = ft_strsplit(line, ' ');
	free(line);
	if (!(line_nb = get_number_from_str(tab_nb, &ret)))
		return (NULL);
	if (!(elem = ft_lstnew(line_nb, ret * sizeof(int))))
		return (NULL);
	free_char_split(tab_nb);
	return (elem);
}

void		get_size(t_list *begin, int *max_x, int *max_y)
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
	*max_y = y_max;
}

int			**continu_get_map(int **tab, int *line, t_list *elem, int *max)
{
	int	i;
	int	j;

	j = max[1];
	while (j >= 0)
	{
		if (!(tab[j] = (int*)malloc(sizeof(int) * max[0])))
			return (NULL);
		ft_bzero(tab[j], sizeof(int) * max[0]);
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

int			**get_map_lst(t_list *begin, int *max_x, int *max_y)
{
	int		*line;
	int		**tab;
	int		max[2];

	line = NULL;
	if (!begin || !max_x || !max_y)
		return (NULL);
	get_size(begin, max_x, max_y);
	if (!(tab = (int **)malloc(sizeof(int*) * *max_y)))
		return (NULL);
	max[0] = *max_x;
	max[1] = *max_y - 1;
	return (continu_get_map(tab, line, begin, max));
}

int		free_the_node(t_list *elem)
{
	t_list	*tmp;

	while (elem)
	{
		tmp = elem->next;
		free(elem->content);
		free(elem);
		elem = tmp;
	}
	return (1);
}

int	**get_the_map(int fd, int *x_max, int *y_max)
{
	t_list	*elem;
	t_list	*begin;
	int		**map;

	begin = NULL;
	while ((elem = read_line_number(fd)))
	{
		elem->next = begin;
		begin = elem;
	}
	if (!(map = get_map_lst(begin, x_max, y_max)))
	{
		if (errno)
			perror(maps_name(NULL));
		else
			ft_putstr("Error on getting the map");
	}
	free_the_node(begin);
	close(fd);
	return (map);
}
