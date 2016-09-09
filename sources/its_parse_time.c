/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   its_parse_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 16:43:26 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/09 16:52:56 by fjanoty          ###   ########.fr       */
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

void	ft_replace(char *str, char *to_find, char replace)
{
	int	i;

	i = 0;
	if (!str || !to_find)
		return ;
	while (str[i])
	{
		if (ft_strrchr(to_fine, str[i]) != 0)
			str[i] = replace;
		i++:
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

int		*get_number_from_str(char **char_nb, *size)
{
	int	*tab_nb;
	int	i;

	if (!size)
		return (NULL);
	*size = ft_tablen(char_nb);
	if (*size <= 0 || !(tab_nb = (int*)malloc(*size * sizeof(int))))
		return (NULL);	
	while (i < *size)
	{
		tab_nb[i] = ft_atoi(char_nb[i]);
		i++:
	}
	return (tab_nb);
}

t_list	*read_line_number(int fd)
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
	if (!(line_nb = get_number_from_str(tab_nb, &ret)))
		return (NULL);
	if (!(elem = ft_lstnew(line_nb, ret)))
		return (NULL);
	return (elem);
}
