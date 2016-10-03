/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/30 04:01:28 by fjanoty          ###   ########.fr       */
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

double		wave_valu(double coef2, double cnt, double *max, double i, double j, double cx, double cy)
{
//	int			sign;
	int			k;
	double		dist;
	double		add;
//	double		coef;
	double		amort;
(void)max;

	dist = ((i - cx) * (i - cx)) + ((j - cy) * (j - cy));
	dist = sqrt(dist);
	dist /= 0.8;
//	coef = ((dist + cnt) / (1 + ((dist / max[0] / 4) * cnt / 20)));
	amort = ( dist / (cnt / (10) + 1) + 1);
	add = cos((coef2 +  0.5 * dist / (1 +  cnt * 10)));
//	add = sin(coef2 + dist) + 1.7 * sin(coef2 / 2.3 + dist) + 0.3 * sin(coef2 / 3.5 + dist) + 0.1 * sin(coef2 / 4.1 + dist) + 0.2 * sin(coef2 / 5.2 + dist);
	add *= 700 + 0*k;
	add /= amort;
//	sign = (add > 0) ? 1 : -1;
//	add = log(ABS(add)) * sign * 10;

	return (add);
}

//	en fonction d'une distance au centre et du temps;
t_matrix	***finishe_get_map(double **tab, int *vect_nb, double *max, t_env *e)
{
	t_matrix	***map_mat;
	static	int		k = 0;
	int				j;
	int				i;
	static	double	cnt = 0;
	static	double	coef2 = 0;

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
			vect_nb[0] = (i - (max[0] * 0.5)) * ((e->ecr_x * 0.75) / max[0]);
			vect_nb[1] = (j - (max[1] * 0.5)) * ((e->ecr_y * 0.75) / max[1]);
			vect_nb[2] = ((2) * (100 * ((tab[j][(i + k) % (int)max[0]] - ((e->z_max - e->z_min) / 2))) / (max[2])));
//			vect_nb[2] += wave_valu(coef2, cnt, max, i, j, max[0] * 0.1, max[1] * 0.1); 
//			vect_nb[2] += wave_valu(coef2 * 1.1, cnt, max, i, j, max[0] * 0.8, max[1] * 0.8);
//			vect_nb[2] += wave_valu(coef2 * 1.2 + M_PI * 1.1, cnt, max, i, j, max[0] / 2 + sin(coef2) * cnt, max[1] / 2 + cos(coef2) * cnt);
			map_mat[j][i] = vect_new_verti(vect_nb, 3);
			i++;
		}
		j++;
	}
	k++;
	cnt += 0.05;
	coef2 += 0.2 / (1 + cnt / (7 * M_PI));
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
	double		dist;
	static	double	cnt = 0;

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
			dist = ((i - max[0] * 0.5) * (i - max[0] * 0.5)) + ((j - max[1] * 0.5) * (j - max[1] * 0.5));
			dist = sqrt(dist);
			dist /= 4;
			result = (((20 * sin(dist + cnt) + (100 * ((tab[j][i] - ((e->z_max - e->z_min) / 2))) / (max[2]))) / ((dist + 0.5) / 6 + 0.2)) / (1 * max[2])) + max[4]; 
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
	cnt += 0.3;
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
	max[3] = e->ecr_y * 1.5 / 5.0;	// r1
	max[4] = max[3] * 3.0 / 5.0;	// r2
	if (!(tab = cast_tab(e->map, max[0], max[1])))
		return (NULL);
	if (e->view % 3 == 0)
		return (finishe_get_map(tab, vect_nb, max, e));
	else if (e->view % 3 == 1)
	{
		max[3] = 0;	// r1
		return (finishe_get_map_circle(tab, vect_nb, max, e));
	}
	else
		return (finishe_get_map_torus(tab, vect_nb, max, e));
}
