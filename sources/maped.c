/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/13 10:56:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "c_maths.h"

void		print_the_map(t_matrix ***map)
{
	int	i;
	int	j;

	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			dprintf(1, "%f	", map[j][i]->m[Y]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
	dprintf(1, "\n\n\n\n\n");
//	sleep(10);
}


t_matrix	***get_map(double *z_max, double *z_min, t_env *e)
{
	t_matrix	***map_mat;
	int			**tab;
	int			x_max;
	int			y_max;
	int			i;
	int			j;
//	double		z_max;
//	double		z_min;

//	dprintf(1, "D\n");
/*
	int			tab2[10][10]		=	{{0, 0, 0,-0,-0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0,-0, 0, 0, 0,-0, 0, 0,-0, 0},
										{ 0,-0,-0, 0,-0, 0, 0, 0,-0,-0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{ 0,-0,-0, 0, 0, 0, 0, 0, 0, 0},
										{ 0, 0, 0, 0, 0, 0,-0, 0, 0, 0},
										{-0,-0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0, 0, 0,-0, 0,-0, 0, 0, 0, 100}};

	int			tab1[10][10]	=	{{-6,-67,-61,-38,  9,-16,-16, 32, 56, 16},
									{ 27,-63, 23,-56, 63, 10, 33, -9,-55, 69},
									{-44,-23,-58, 12,-55,  0, 21,-25, 27, 48},
									{  1, 41,-38, 57, 38,-17,-50, -2,-63, 7},
									{ 32,-46,-11, 30, 10, 13,-48,-37, 66,-53},
									{-54, 34, 51,-40,-33, 52,-62,-37,-54,-9},
									{-58, 40,-30, -9, 59,  7,-66,-12,-18, 41},
									{-50, 67, 36, 13, 12, -2,-28, 10,-60,-58},
									{  3,-27,-52, 56, 26,-52, 59,-31,-48,-6},
									{-59,-30, 50, 36,  5,-11,  0, 60,-24,-34}};
*/
//	(void)tab2;
//	(void)tab1;
	if (!e)
		return (NULL);
	tab = e->map;
	x_max = e->size_map_x;
	y_max = e->size_map_y;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * y_max)))
		return (NULL);
	j = 0;
//	dprintf(1, "x_max:%d	y_max:%d\n", x_max, y_max);
	while (j < y_max)
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * x_max)))
			return (NULL);
		while (i < x_max)
		{
			*z_max = MAX(tab[j][i], *z_max);
			*z_min = MIN(tab[j][i], *z_min);
			map_mat[j][i] = matrix_put_in_new((double)i, (double)j, tab[j][i], 0);
//			dprintf(1, "before\n");
//			matrix_display(map_mat[j][i]);
//			dprintf(1, "after [%d]\n", i);
//			matrix_buffer(map_mat[j][i]);
//			matrix_put_in((i - 5) * 30, (j - 5) * 30, tab[j][i] / 2, 1);
			i++;
		}
//			dprintf(1, "after2	[%d]\n", j);
		j++;
	}
//	dprintf(1, "F\n");
	print_the_map(map_mat);
	return (map_mat);
}
