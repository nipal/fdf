/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/18 04:34:42 by fjanoty          ###   ########.fr       */
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
			dprintf(1, "%f	", map[j][i]->m[Z]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
	dprintf(1, "\n");
//	sleep(10);
}

void		actu_vect_nb(int *vect_nb, int x, int y, int z)
{
	if (!(vect_nb))
	{
		dprintf(1, "you fucked-up");
		return ;
	}
	vect_nb[0] = x;
	vect_nb[1] = y;
	vect_nb[2] = z;
}

//	il faudrAIT FAIRE UNE SYSTEM DE COPY...
//	
//
//		Pour faire le scaling on veux la taille de l'ecran
//

//	(i - (x_max / 2)) * ((e->ecr_x * 1.25) / x_max)
//	(j - (y_max / 2)) * ((e->ecr_y * 1.25) / y_max)

t_matrix	***get_map(t_env *e)
{
	t_matrix	***map_mat;
	int			**tab;
	int			x_max;
	int			y_max;
	int			i;
	int			j;
	int			*vect_nb;

	if (!(vect_nb = (int*)malloc(sizeof(int) * 3)))
	{
		dprintf(1, "NOOOOOOOOOOOOOOOOOOOOOON	--> malloc error\n");
		return (NULL);
	}
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
			/*
			actu_vect_nb(vect_nb
			,(i - 0 * (x_max / 2)) * ((e->ecr_x * 0.5) / x_max)
			 ,(j - 1 * (y_max / 2)) * ((e->ecr_y * 0.5) / y_max)
			 , ((tab[j][i] - ((e->z_max - e->z_min)) / 2))/(e->z_max - e->z_min) * 50 );
			 */
			vect_nb[0] = (i - (x_max * 0.5)) * ((e->ecr_x * 0.5) / x_max);
			vect_nb[1] = (j - (y_max * 0.5)) * ((e->ecr_y * 0.5) / y_max);
			vect_nb[2] = 50 * ((tab[j][i] - ((e->z_max - e->z_min) / 2)))/(e->z_max - e->z_min);
		
//			*z_max = MAX(tab[j][i], *z_max);
//			*z_min = MIN(tab[j][i], *z_min);
			map_mat[j][i] = vect_new_verti(vect_nb, 3);
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
//	dprintf(1, "-------------------------------------------------------\n");
//	print_the_map(map_mat);
//	dprintf(1, "#######################################################\n");
	return (map_mat);
}
