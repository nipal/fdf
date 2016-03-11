/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:44:11 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/10 09:38:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
# define BUFFER 100

/*
int		fill_mapstr(t_list **begin, int *nbr)
{
	int		oct_lu;
	t_list	*elem;
	t_list	*prev;


	if (!begini || !*begin
			|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * BUFFER), 0)))
		return (0);
	*begin = elem;
	oct_lu = read(fd, elem->content, BUFFER);
	*nbr += oct_lu;
	elem->content_size = oct_lu;
	while (oct_lu == BUFFER)
	{
		prev = elem;
		if (!(elem = ft_lstnew((char*)malloc(sizeof(char) * BUFFER), 0))
			|| oct_lu = read(fd, elem->content, BUFFER) < 0)
			return (0);
		elem->content_size = oct_lu;
		prev->next = elem;
	}
	return (1);
}

char	*malloc_str(t_list	*data, size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	while (data)
	{
		ft_memamove(str, data->content, data->content_size);
		data = data->next;
		str += data->content_size;
	}
	return (str);
}

int		fill_line(char *str, t_list **begin)
{
	int		nb_ligne;
	int		size;
	t_list	*elem;
	t_list	*prev;


	nb_ligne = 0;
	if (!str || !begini || !*begin 
		|| !(size = ft_strchr((char*)*(begin)->content, '\n'))
		|| !(size = ft_strlen((char*)*(begin)->content))
		|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * size), size)))
		return (-1);
	*begin = elem;
	ft_memmove(elem->content, str, size);
	str += size;
	while (oct_lu == BUFFER)
	{
		prev = elem;
		if (!(size = ft_strchr((char*)*(begin)->content, '\n'))
			|| !(size = ft_strlen((char*)*(begin)->content))
			|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * size), size)))
			return (0);
		prev->next = elem;
		ft_memmove(elem->content, str, size);
		str += size;
		nb_ligne++;
	}
	return (nb_ligne);
}

t_matrix	**fill_the_real_map(int	x, int y)
{
	t_matrix	***map;
	int			j;

	***map = (t_matrix***)malloc(sizeof(t_matrix**) * y);
	j = 0;
	while (j < y)
	{
		**map = (t_matrix**)malloc(sizeof(t_matrix*) * x);
		i = 0;
		while ();
		j++;
	}
}

//	on recupere une chaine de caractere
//	on rend chanque ligne dans des liste
//	on malloque le tbleaud e table
//	on le remplis avec la piste
//	count word/ cheque if 
*/
int						parse(int fd)
{
	int		map;
	t_list	*begin;

	(void)map;
	(void)fd;
	(void)begin;
	return (1);
}
//*/
//	on 
