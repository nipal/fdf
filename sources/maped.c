/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/13 11:58:04 by fjanoty          ###   ########.fr       */
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


t_matrix	***get_map(double *z_max, double *z_min)
{
	t_matrix	***map_mat;
	int			x;
	int			y;
	int			i;
	int			j;
//	double		z_max;
//	double		z_min;

//	dprintf(1, "D\n");
	int			tab1[10][10]		=	{{1, 0, 0,-1,-1, 0, 1, 1, 0, 0},
										{-1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
										{-1, 1, 0, 0,-1, 1, 0, 0, 0, 1},
										{ 1,-1, 0, 1, 1,-1, 0, 0,-1, 0},
										{ 1,-1,-1, 0,-1, 0, 0, 0,-1,-1},
										{-1, 1, 0, 1, 1, 0, 1, 0, 0, 0},
										{ 0,-1,-1, 0, 0, 1, 0, 0, 0, 1},
										{ 0, 0, 0, 0, 1, 0,-1, 0, 0, 0},
										{-1,-1, 0, 1,-1, 0, 1, 0, 0, 1},
										{ 0, 0, 1,-1, 0,-1, 0, 0, 0, 0}};
	(void)tab1;

	int			tab2[10][10]	=	{{-6,-67,-61,-38,  9,-16,-16, 32, 56, 16},
									{ 27,-63, 23,-56, 63, 10, 33, -9,-55, 69},
									{-44,-23,-58, 12,-55,  0, 21,-25, 27, 48},
									{  1, 41,-38, 57, 38,-17,-50, -2,-63, 7},
									{ 32,-46,-11, 30, 10, 13,-48,-37, 66,-53},
									{-54, 34, 51,-40,-33, 52,-62,-37,-54,-9},
									{-58, 40,-30, -9, 59,  7,-66,-12,-18, 41},
									{-50, 67, 36, 13, 12, -2,-28, 10,-60,-58},
									{  3,-27,-52, 56, 26,-52, 59,-31,-48,-6},
									{-59,-30, 50, 36,  5,-11,  0, 60,-24,-34}};

	(void)tab2;
	x = 10;
	y = 10;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * x)))
			return (NULL);
		while (i < x)
		{
			if (!(map_mat[j][i] = matrix_init(4, 1)))
				return (NULL);
			*z_max = MAX(tab2[j][i], *z_max);
			*z_min = MIN(tab2[j][i], *z_min);
			matrix_buffer(map_mat[j][i]);
			matrix_put_in(i, j, tab2[j][i], 1);
			i++;
		}
		j++;
	}
//	dprintf(1, "F\n");
//	print_the_map(map_mat);
	return (map_mat);
}
