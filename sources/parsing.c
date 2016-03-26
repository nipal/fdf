#include "fdf.h"

/*
on resoi un file descriptor et on en retir
*/


t_list	*get_file(int fd)
{
	int		ret;
	t_list	*begin;
	char	buff[SIZE_BUFF + 1];

	begin = NULL;
	while ((ret = read(fd, buff, SIZE_BUFF)) > 0)
		ft_lstadd_back(&begin, ft_lstnew(buff, ret));
	return (begin);
}

char	*get_str(t_list *lst)
{
	int		size;
	int		i;
	char	*str;

	if (!lst)
		return (NULL);
	i = 0;
	size = ft_lstsize(begin);
	if (!(str = ft_strnew(SIZE_BUFF * size)))
		return (NULL);
	while (i < size)
	{
		ft_memcpy(i * SIZE_BUFF + str, lst->content, lst->size);
		str[i * SIZE_BUFF + lst->size] = '\0';
		lst = lst->new; 
	}
	return (str);
}

int		get_tabsize(char **tab)
{
	int	size;

	size = 0;
	if (!tab)
		return (0);
	while (tab[size])
		size++;
	return (size);
}

int		free_charab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

int		**get_number(char *str, int *size_line, int *nb_line)
{
	char	**line;
	char	**tmp;
	int		**map;
	int		i;
	int		j;

	if (!size_line || !nb_line || !(line = ft_strsplit(str, '\n')))
		return (NULL);
	*nb_line = get_tab_size(line);
	if (!(map = (int**) malloc(sizeof(int*) * size)))
		return (NULL);
	if (!(tmp = ft_strsplit(line[0], ' '))) 
		return (NULL);
	j = 0;
	while (j < *nb_line)
	{
		j++;
	}
}
