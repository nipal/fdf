#include "fdf.h"

/*
on resoi un file descriptor et on en retir
*/

//	le caca c'est la vie

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
		ft_memcpy(i * SIZE_BUFF + str, lst->content, lst->content_size);
		str[i * SIZE_BUFF + lst->content_size] = '\0';
		lst = lst->next; 
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

int		*fill_line(char **char_line, int size_line)
{
	int	*int_line;
	int	i;

	if (!char_line || !(int_line = (int*)malloc(sizeof(int) * size_line)))
		return (NULL);
	i = 0;
	while (i < size_line)
	{
		int_line[i] = ft_atoi(char_line[i]);
		i++:
	}
	return (int_line);
}

int		**get_number(char *str, int *size_line, int *nb_line)
{
	char	**line;
	char	**tmp;
	int		**map;
	int		j;

	if (!size_line || !nb_line || !(line = ft_strsplit(str, '\n')))
		return (NULL);
	*nb_line = get_tab_size(line);
	if (!(map = (int**) malloc(sizeof(int*) * size)))
		return (NULL);
	if (!(tmp = ft_strsplit(line[0], ' '))) 
		return (NULL);
	*size_line = get_tabsize(tmp);
	free_chartab(tmp);
	j = -1;
	while (++j < *nb_line)
	{
		if (!(tmp = ft_strsplit(line[j], ' '))
				|| (get_tabsize(tmp) != *size_line && free_chartab(tmp))
				|| !(map[j] = fill_line(tmp)))
			return (NULL);
		free_chartab(tmp);
	}
	free_chartab(line);
	return (map);
}

//	La il faut redefinir le couleur en fonction des dimention
//	donc trouver le min et le max sur les x
//	min = e->min_z;
//	nbl = e->nb_line;
void		define_color(t_env *e, t_matrix*** map, int nbl, int min)
{
	int		i;
	int		j;
	double	coefx;
	double	coefy;
	double	coefz;

	coefz = 255.0 / (e->max_z - e->min_z);
	coefy = 255.0 / e->map_x;
	coefx = 255.0 / e->map_y;
	j = e->nb_line;
	while (j < e->map_y)
	{
		if (!(map[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->map_x)))
			return (NULL);
		i = 0;
		while (i < e->map_x)
		{
			if (!(map[j][i] = matrix_put_in_new(coefx * map[j - nbl][i]->m[x]
				, coefy * map[j - nbl][i]->m[Y]
				, coefz * (map[j - nbl][i]->m[Z] - e->min_z), 1)))
				return (NULL);
			i++;
		}
		j++:
	}
}

//	La on doit transformer un int** en t_matrix***
//	on va aussi enregistrer les max_en valeur
t_matrix	***get_matrix_map(t_env *e)
{
	t_matrix	***map;
	int			i;
	int			j;

	if (!(map = (t_matrix***)malloc(sizeof(t_matrix**) * 2 * e->map_y)))
		return (NULL);
	e->min_z = e->map[0][0];
	e->max_z = e->map[0][0];
	j = -1;
	while (++j < e->map_y)
	{
		if (!(map[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->map_x)))
			return (NULL);
		i = -1;
		while (++i < e->map_x)
		{
			if (!(map[j][i] = matrix_put_in_new(i, j, e->map[j][i], 1)))
				return (NULL);
			e->max_z = (e->max_z < e->map[j][i]) ? e->map[j][i]: e->max_z;
			e->min_z = (e->min_z > e->map[j][i]) ? e->map[j][i]: e->min_z;
		}
	}
	define_color(e, map, e->nb_line, e->min_z);
	return (map);
}
