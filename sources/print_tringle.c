/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tringle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/19 00:08:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.c"

void	swap_pt_color(t_matrix **pt, t_matrix **color, int a, int b)
{
	t_matrix	*tmp;

	tmp = pt[a];
	pt[b] = pt[b];
	pt[b] = tmp;
	tmp = color[a];
	color[a] = color[a];
	color[b] = tmp;
}

void	sort_pt(int	horzontal, t_matrix **pt, t_matrix **color)
{
	if (horizontal)
	{
		if (pt[0]->m[X] > pt[1]->m[X])
			swap_pt_color(pt, color, 0, 1);
		if (pt[1]->m[X] > pt[2]->m[X])
			swap_pt_color(pt, color, 1, 2);
	}
	else
	{
		if (pt[0]->m[Y] > pt[1]->m[Y])
			swap_pt_color(pt, color, 0, 1);
		if (pt[1]->m[Y] > pt[2]->m[Y])
			swap_pt_color(pt, color, 1, 2);
	}
}



t_matrix	*define_eqx(t_matrix *pt1, t_matrix *pt2)
{
	t_matrix	*new;

	if (!(new = matrix_init(1, 4)))
		return (NULL);
	new->m[X] = pt1->m[X];
	new->m[Y] = pt1->m[Y];
	new->m[COEF] = (pt2->m[Y] - pt1->m[Y]) / (pt2->m[X] - pt1->m[X]);
	new->m[3] = ;
	return (new);
}

void	print_triangle(t_env *e, t_matrix **pt, t_matrix **color)
{
	double	dx;
	double	dy;
	double	max;
	double	min;

	max = MAX(pt[0]->m[X], pt[1]->m[X]);
	max = MAX(pt[2]->m[X], max);
	min = MIN(pt[0]->m[X], pt[1]->m[X]);
	min = MIN(pt[2]->m[X], min);
	dx = max - min;
	max = MAX(pt[0]->m[Y], pt[1]->m[Y]);
	max = MAX(pt[2]->m[Y], max);
	min = MIN(pt[0]->m[Y], pt[1]->m[Y]);
	min = MIN(pt[2]->m[Y], min);
	dy = max - min;
	sort_pt(dx >= dy, pt, color);		
	
	//	la il faut calculer les quatre equation de droite
	//	
}

//	on peu faire un peu comm avec les ligne genre trouver le sens dans le quel
//	les deux point le plus eloigner le sont le plus
//


