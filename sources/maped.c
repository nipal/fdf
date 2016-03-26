/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/25 01:38:53 by fjanoty          ###   ########.fr       */
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


t_matrix	***get_map(t_env *e, double *z_max, double *z_min)
{
	t_matrix	***map_mat;
	int			x;
	int			y;
	int			i;
	int			j;
//	double		z_max;
//	double		z_min;

//	dprintf(1, "D\n");
//

/*
	int			tab2[10][10]		=	{{-100, 0, 0,-0,-0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0,-0, 0, 0, 0,-0, 0, 0,-0, 0},
										{ 0,-0,-0, 0,-0, 0, 0, 0,-0,-0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{ 0,-0,-0, 0, 0, 0, 0, 0, 0, 0},
										{ 0, 0, 0, 0, 0, 0,-0, 0, 0, 0},
										{-0,-0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0, 0, 0,-0, 0,-0, 0, 0, 0, 100}};
#define Y 10
#define X 10
//*/

/*
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
#define Y 10
#define X 10
*/

//*
int	tab2[11][19] =		{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0},
			{0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0},
			{0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0},
			{0, 0, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 10, 10, 10, 10, 0, 0, 0},
			{0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//#define Y 11
//#define X 18
//*/

	(void)tab2;
//	(void)tab1;
	x = 11;
	y = 18;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * 2 * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * x))
			|| !(map_mat[j + y] = (t_matrix**)malloc(sizeof(t_matrix*) * x)))
			return (NULL);
		while (i < x)
		{
			if (!(map_mat[j][i] = matrix_init(1, 4))
				|| !(map_mat[j + y][i] = matrix_init(1, 4)))
				return (NULL);
			*z_max = MAX(tab2[j][i], *z_max);
			*z_min = MIN(tab2[j][i], *z_min);
			matrix_buffer(map_mat[j][i]);
			matrix_put_in((i - 5) * 30, (j - 5) * 30, (tab2[j][i] * e->zoom * 0.01), 1);
			matrix_buffer(map_mat[j + y][i]);
			matrix_put_in((i - 5) * 30, (j - 5) * 30, (tab2[j][i] * e->zoom * 1), 1);
			i++;
		}
		j++;
	}
//	dprintf(1, "F\n");
//	print_the_map(map_mat);
	return (map_mat);
}
