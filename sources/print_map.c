/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 17:57:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	define_color(t_matrix *point, t_matrix *color)
{
	if (point && color)
	{
		color->m[R] = 100;
		color->m[G] = 100;
		color->m[B] = 128 - 2 * point->m[Z];
	}
}

void	get_point(t_matrix ***map, t_matrix **point, int i, int j)
{
	int	k;

	if (!(point[0] = (i < 10 && j < 10) ? matrix_copy(map[j][i]) : NULL)
		|| !(point[1] = (i < 9 && j < 10) ? matrix_copy(map[j][i + 1]) : NULL)
		|| !(point[2] = (j < 9 && i < 10) ? matrix_copy(map[j + 1][i]) : NULL)
		|| !(point[3] =
			(j < 9 && i < 9) ? matrix_copy(map[j + 1][i + 1]) : NULL))
		;
	k = 0;
	while (k < 4)
	{
		if (point[k])
			define_color(point[k], point[k + 4]);
		else
			point[k] = NULL;
		k++;
	}
}

int		is_visible(t_matrix **corner, t_matrix *pt)
{
	int		i;
	double	result;

	i = 0;
	if (pt->m[Z] < 0)
		return (0);
	while (i < 4)
	{
		if ((result = matrix_dot_product(corner[i], pt)) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	draw_link(t_env *e, t_cam *cam, t_matrix **pt)
{
	if (pt[0] && is_visible(cam->corner, pt[0]))
	{
		if (pt[1] && pt[1]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[1], pt[4], pt[5]));
		if (pt[2] && pt[2]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[2], pt[4], pt[6]));
		if (pt[3] && pt[3]->m[Z] > 0)
			draw_line(e, init_mat_line(pt[0], pt[3], pt[4], pt[7]));
	}
}

void	free_point(t_matrix ***pt, int size_x, int size_y)
{
	int					i;
	int					j;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			matrix_free(pt[j] + i);
			i++;
		}
		j++;
	}
}

int		init_color(t_matrix **point)
{
	int	i;

	i = 4;
	while (i < 8)
	{
		if (!(point[i] = matrix_init(1, 4)))
			return (0);
		i++;
	}
	return (1);
}

void	print_map(t_env *e, t_cam *cam, t_matrix ***map)
{
	int					i;
	int					j;
	static	t_matrix	**point = NULL;

	if (!cam || !map || !*map || !**map)
	{
		dprintf(1, "error\n");
		return ;
	}
	j = 0;
	if ((!point && (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))
					|| !init_color(point))))
		return ;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			i++;
		}
		j++;
	}
}
