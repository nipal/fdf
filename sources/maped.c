/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/27 17:45:25 by fjanoty          ###   ########.fr       */
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

t_matrix	***finishe_get_map(int **tab, int *vect_nb, int *max, t_env *e)
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

t_matrix	***get_map(t_env *e)
{
	int			**tab;
	int			max[3];
	int			*vect_nb;

	if (!(vect_nb = (int*)malloc(sizeof(int) * 3)) || !e)
		return (NULL);
	tab = e->map;
	max[0] = e->size_map_x;
	max[1] = e->size_map_y;
	max[2] = ((e->z_max - e->z_min)) ? (e->z_max - e->z_min) : 1;
	return (finishe_get_map(tab, vect_nb, max, e));
}
