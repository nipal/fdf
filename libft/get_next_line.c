/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 15:02:25 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/10 07:33:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_strmchr(char *s, int c)
{
	char	*p;

	if (!s)
		return (0);
	if (c == 0)
		return (ft_strlen(s));
	p = ft_strchr(s, c);
	if (p)
	{
		return ((int)(p - s));
	}
	return (ft_strlen(s));
}

char		*ft_str_magic(char *str1, char *str2)
{
	int		max1;
	int		max2;
	char	*result;

	if (!str1 || !str2)
		return (NULL);
	max1 = ft_strmchr(str1, '\n');
	max2 = ft_strmchr(str2, '\n');
	if (!(result = ft_strnew(1 + ft_strlen(str1) + ft_strlen(str2))))
		return (NULL);
	ft_strncat(result, str1, max1);
	ft_strncat(result + ft_strlen(str1), str2, max2);
//	free(str1);
	return (result);
}

char		*str_line(int fd, char **rest, int *ret)
{
	int		again;
	char	*line;
	char	*buffer;
	char	*tmp;

//	dprintf(1, "	@@1 ");
	line = ft_strnew(BUFF_SIZE + 1);
//	dprintf(1@@2 ");
	buffer = ft_strnew(BUFF_SIZE + 1);
//	dprintf(1, "	@@3 ");
	ft_memmove(buffer, *rest, MIN(ft_strlen(*rest), BUFF_SIZE));
//	dprintf(1, "	@@4 ");
	buffer = ft_strcpy(buffer, *rest);
//	dprintf(1, "	@@5 ");
	again = (!(ft_strchr(buffer, '\n')));
//	dprintf(1, "	@@6 ");
	line = ft_strncpy(line, buffer, ft_strmchr(buffer, '\n'));
//	dprintf(1, "	@@7 ");
	*ret = 1;
	while (again == 1)
	{
//		dprintf(1, " [$$1");
		ft_bzero(buffer, BUFF_SIZE);
//		dprintf(1, " $$2");
		*ret = read(fd, buffer, BUFF_SIZE);
//		dprintf(1, "ret:%d	", *ret);
//		dprintf(1, " $$3");
		line = ft_str_magic(line, buffer);
//		dprintf(1, " $$4");
		again = ((!(ft_strchr(buffer, '\n'))) && *ret == BUFF_SIZE);
//		dprintf(1, " $$5]");
	}
//	free(*rest);
//	dprintf(1, " end]]");
	*rest = ft_strnew(BUFF_SIZE + 1);
//	dprintf(1, "	@@8 ");
	tmp = ft_strnew(BUFF_SIZE + 1);
//	dprintf(1, " (b)%ld ", (long)buffer);
//	dprintf(1, " (f)%ld ", (long)(ft_strmchr(buffer, '\n')));
//	dprintf(1, " (a)%ld ", (long)(buffer + 1 + ft_strmchr(buffer, '\n')));
//	dprintf(1, "	(s)-->%s<--(s) ", buffer);;
//	dprintf(1, "	(r)-->%s<---(r)	", (char *)(buffer + 1 + ft_strmchr(buffer, '\n')));
	*rest = ft_strcpy(tmp, buffer + 1 + ft_strmchr(buffer, '\n'));
//	dprintf(1, "	@@9\n");
//	free(buffer);
	return (line);
}

t_fdgnl		*get_creat_elem(t_fdgnl **begin, int fd)
{
	t_fdgnl	*elem;

	if (!begin)
		return (NULL);
	elem = *begin;
	while (elem && elem->fd != fd)
		elem = elem->next;
	if (!elem)
	{
		if (!(elem = (t_fdgnl*)malloc(sizeof(t_fdgnl))))
			return (NULL);
		elem->fd = fd;
		elem->rest = ft_strnew(1 + BUFF_SIZE);
		elem->next = *begin;
		*begin = elem;
	}
	return (elem);
}

int			get_next_line(int fd, char **line)
{
	static	t_fdgnl	*begin = NULL;
	t_fdgnl			*elem;
	char			*str;
	int				ret;

	ret = -1;
//	dprintf(1, "__1\n");
	if (fd < 0 || !line)
		return (-1);
//	dprintf(1, "__2\n");
	elem = get_creat_elem(&begin, fd);
//	dprintf(1, "__3\n");
	str = str_line(elem->fd, &(elem->rest), &ret);
//	dprintf(1, "__4\n");
	*line = str;
//	dprintf(1, "__5\n");
	if (ret < 0)
		return (-1);
//	dprintf(1, "__6\n");
	return (*line != NULL && ((ret > 0) || (ft_strlen(*line) > 0)));
}
