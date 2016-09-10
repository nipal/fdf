/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/10 07:30:21 by fjanoty          ###   ########.fr       */
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
//	dprintf(1, " {%d} ", ft_atoi(char_nb[i]));
//	dprintf(1, " [%d] ", tab_nb[i]);
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
//	dprintf(1, "	str[%d]	:%s:	", i, tab[i]);
		i++;
	}
//	dprintf(1, "\n");
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
	print_char_tab(tab_nb);
	if (!(line_nb = get_number_from_str(tab_nb, &ret)))
		return (NULL);
//	dprintf(1, "ret:	((%d))\n", ret);
	if (!(elem = ft_lstnew(&line_nb, ret)))
		return (NULL);
//	dprintf(1, "ending\n");
	return (elem);
}
	//dprintf(1, "\n");
