/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paseur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 05:35:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/21 17:44:48 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	on recupere tout un fichier
//	on le decoupe en mot et en ligne
//		si il y a autre chose que des nombre
//		ou que la map n'est pas un rectangle
//			on quite
//
//
//	ft_atoi_base magic
//	on definie la camera
//	on fait les projection
//	on deplace la camera
//	on gere les couleur joliment (luminosite si loin)
//	on prend 2  map en entrer et on fait un plafond (ou carrement autant de sole que l'on veux)

#define SIZE_BUFF 1024

char	*get_file_to_str(int fd)
{
	t_list	*begin;
	t_list	*elem;
	char	*str;
	int		ret;
	int		sum;

	if (!(str = malloc(sizeof(char) * (SIZE_BUFF + 1))))
		return (NULL);
	sum = 0;
	while ((ret = read(fd, str, SIZE_BUFF)))
	{
		sum += ret;
		str[ret] = '\0';
		elem = ft_lstnew(ft_strdup, ret);
		ft_lstadd_back(elem);
	}
	if (!(str = malloc(sizeof(char) * (sum + 1))))
		return (NULL);
	elem = begin;
	sum = 0;
	while (elem)
	{
		ft_memmove(str + sum, elem->content, elem->content_size);
		sum += elem->content_size;
		elem = elem->next;
	}
	return (str);
}

int		**parsing(int fd)
{
	int		**tab;
	char	**

	return (tab);
}
