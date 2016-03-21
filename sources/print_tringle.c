/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tringle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/20 18:20:31 by fjanoty          ###   ########.fr       */
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

/*
 *	les point sont ranger par ordre croissant
 *	selon les x ou le y
 * */
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
	new->m[COEF] = ABS((pt2->m[Y] - pt1->m[Y]) / (pt2->m[X] - pt1->m[X]));
	new->m[3] = pt2->m[X] - pt1->m[X];
	return (new);
}

t_matrix	*define_eqy(t_matrix *pt1, t_matrix *pt2)
{
	t_matrix	*new;

	if (!(new = matrix_init(1, 4)))
		return (NULL);
	new->m[X] = pt1->m[X];
	new->m[Y] = pt1->m[Y];
	new->m[COEF] = ABS((pt2->m[X] - pt1->m[X]) / (pt2->m[Y] - pt1->m[Y]));
	new->m[3] = pt2->m[Y] - pt1->m[Y];
	return (new);
}

t_matrix	**lst_eq(int is_horizontal, t_matrix **pt, t_matrix **color)
{
	t_matrix 	**eq;
	t_matrix	*t_b;
	t_matrix	*t_m;
	t_matrix	*m_b;
	
	if (!(eq = (t_matrix**)malloc(sizeof(t_matrix*) * 4)))
		return (NULL);
	if (!(is_horizontal))
	{
		t_b = define_eqx(pt[0], pt[2]);
		t_m = define_eqx(pt[0], pt[1]);
		m_b = define_eqx(pt[1], pt[2]);
		//	si faut redefinir une equation avec la position initiale du truc au milieu
	}
	return (eq);
}

/*
 **	la on recupere la equation des bon ruc et on les stoque la ou il faut
 **	pour de finir les equation on a besoin de (dx, dy), des point trier
 * */


void	print_triangle(t_env *e, t_matrix **pt, t_matrix **color)
{
	double	dx;
	double	dy;
	double	max;
	double	min;
	t_matrix	**eq;

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
	eq = 
	
	//	la il faut calculer les quatre equation de droite
	//	
}

//	on peu faire un peu comm avec les ligne genre trouver le sens dans le quel
//	les deux point le plus eloigner le sont le plus
//


