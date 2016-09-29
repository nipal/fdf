/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/29 22:04:15 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "c_maths.h"

void		actu_vect_nb(int *vect_nb, int x, int y, int z)
{
	if (!(vect_nb))
		return ;
	vect_nb[0] = x;
	vect_nb[1] = y;
	vect_nb[2] = z;
}

t_matrix	***finishe_get_map(double **tab, int *vect_nb, double *max, t_env *e)
{
	t_matrix	***map_mat;
	int			j;
	int			i;

	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * max[1])))
		return (NULL);
	j = 0;
	while (j < max[1])
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * max[0])))
			return (NULL);
		while (i < max[0])
		{
			vect_nb[0] = (i - (max[0] * 0.5)) * ((e->ecr_x * 0.5) / max[0]);
			vect_nb[1] = (j - (max[1] * 0.5)) * ((e->ecr_y * 0.5) / max[1]);
			vect_nb[2] = (100
				* ((tab[j][i] - ((e->z_max - e->z_min) / 2))) / (max[2]));
			map_mat[j][i] = vect_new_verti(vect_nb, 3);
			i++;
		}
		j++;
	}
	return (map_mat);
}


//	On cree une lingne
//	on copy cette ligne avec une transformation
t_matrix	***finishe_get_map_torus(double **tab, int *vect_nb, double *max, t_env *e)
{
	t_matrix	***map_mat;
	t_matrix	*rot_y;
	t_matrix	*tmp;
	double		result;
	int			j;
	int			i;

	(void)e;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * max[1])))
		return (NULL);
	j = 0;
	while (j < max[1])
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * max[0]))
			|| !(rot_y = set_rotate(0, e->dr1 + (j * M_PI * 2) / (max[1] - 1), 0)))
			return (NULL);
		while (i < max[0])
		{
			result = (30 * tab[j][i] / (1 * max[2])) + max[4]; 
			vect_nb[0] = max[3] + result * cos(e->dr2 + ((double)(2 * M_PI * i)) / (max[0] - 1));//(i - (max[0] * 0.5)) * ((e->ecr_x * 0.5) / max[0]);
			vect_nb[1] = max[3] + result * sin(e->dr2 + ((double)(2 * M_PI * i)) / (max[0] - 1));//(j - (max[1] * 0.5)) * ((e->ecr_y * 0.5) / max[1]);
			vect_nb[2] = 0;//(100 * ((tab[j][i] - ((e->z_max - e->z_min) / 2))) / (max[2]));
			
			if (!(tmp = vect_new_verti(vect_nb, 3))
				|| !(map_mat[j][i] = matrix_product(rot_y, tmp)))
				return (NULL);
			i++;
		}
		j++;
	}
	return (map_mat);
}

t_matrix	***finishe_get_map_circle(double **tab, int *vect_nb, double *max, t_env *e)
{
	t_matrix	***map_mat;
	t_matrix	*rot_y;
	t_matrix	*tmp;
	double		result;
	int			j;
	int			i;

	(void)e;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * max[1])))
		return (NULL);
	j = 0;
	while (j < max[1])
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * max[0]))
			|| !(rot_y = set_rotate(0, e->dr1 + (j * M_PI * 2) / (max[1] - 1), 0)))
			return (NULL);
		while (i < max[0])
		{
			result = (30 * tab[j][i] / (1 * max[2])) + max[4]; 
			vect_nb[0] = max[3] + result * cos(e->dr2 + ((double)(M_PI * (i + (max[0] - 1) / 2))) / (max[0] - 1));//(i - (max[0] * 0.5)) * ((e->ecr_x * 0.5) / max[0]);
			vect_nb[1] = max[3] + result * sin(e->dr2 + ((double)(M_PI * (i + (max[0] - 1) / 2))) / (max[0] - 1));//(j - (max[1] * 0.5)) * ((e->ecr_y * 0.5) / max[1]);
			vect_nb[2] = 0;//(100 * ((tab[j][i] - ((e->z_max - e->z_min) / 2))) / (max[2]));
			
			if (!(tmp = vect_new_verti(vect_nb, 3))
				|| !(map_mat[j][i] = matrix_product(rot_y, tmp)))
				return (NULL);
			i++;
		}
		j++;
	}
	return (map_mat);
}

double		**cast_tab(int **tab, int x, int y)
{
	double	**tab_val;
	int		j;
	int		i;

	if (!(tab_val = (double**)malloc(sizeof(double*) * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		if (!(tab_val[j] = (double*)malloc(sizeof(double) * x)))
			return (NULL);
		i = 0;
		while (i < x)
		{
			tab_val[j][i] = (double)tab[j][i];
			i++;
		}
		j++;
	}
	return (tab_val);
}

t_matrix	***get_map(t_env *e)
{
	double		**tab;
	double		max[6];
	int			*vect_nb;

	if (!(vect_nb = (int*)malloc(sizeof(int) * 3)) || !e)
		return (NULL);
	max[0] = e->size_map_x;
	max[1] = e->size_map_y;
	max[2] = ((e->z_max - e->z_min)) ? (e->z_max - e->z_min) : 1;
	max[3] = 300;	// r1
	max[4] = 200;	// r2
	if (!(tab = cast_tab(e->map, max[0], max[1])))
		return (NULL);
	if (10 > 11)
		return (finishe_get_map(tab, vect_nb, max, e));
	else if (9 < 10)
	{
		max[3] = 0;	// r1
		return (finishe_get_map_circle(tab, vect_nb, max, e));
	}
	else
		return (finishe_get_map_torus(tab, vect_nb, max, e));
}
