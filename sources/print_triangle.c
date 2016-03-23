/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/23 11:58:58 by fjanoty          ###   ########.fr       */
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
	t_matrix	*t_b1;
	t_matrix	*t_b2;
	t_matrix	*t_m;
	t_matrix	*m_b;
	
	if (!(eq = (t_matrix**)malloc(sizeof(t_matrix*) * 4)))
		return (NULL);
	if (!(is_horizontal))
	{
		t_b1 = define_eqx(pt[0], pt[2]);
		t_b2 = define_eqx(pt[0], pt[2]);//	mais decaler
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

/*
 *	On determine le coin opposer au coter le plus court
 *	size	= le max des composante des deux vecteur qui parte du point
 *	diff1_pos	= diff du premier vecteur
 *	diff1_col	= diff du premier vecteur
 *	diff2_pos	=
 *	diff2_col	=
 *	on iter le trassage de ligne sur *
 * */

/*
 *	Il faut une fonction qui defini le coin opposer au plus petit segment
 *	donc deux fontion qui definisse le deux plus grand segment
 *	puis le point commun a ces deux segment
 *
 *	on renvoi les coordoner, la size et les differenciels d1, d2, dc1, dc2
 * */

t_matrix	*vect_max_x(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3)
{
	t_matrix	*tmp;

	tmp = MAX(pt1->m[X] > pt2->m[X]) ? pt1 : pt2;
	tmp = MAX(pt3->m[X] > tmp->m[X]) ? pt3 : tmp;
	return (tmp);
}

t_matrix	*vect_max_y(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3)
{
	t_matrix	*tmp;

	tmp = MAX(pt1->m[Y] > pt2->m[Y]) ? pt1 : pt2;
	tmp = MAX(pt3->m[Y] > tmp->m[Y]) ? pt3 : tmp;
	return (tmp);
}
t_matrix	*vect_min_x(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3)
{
	t_matrix	*tmp;

	tmp = MIN(pt1->m[X] < pt2->m[X]) ? pt1 : pt2;
	tmp = MIN(pt3->m[X] < tmp->m[X]) ? pt3 : tmp;
	return (tmp);
}
t_matrix	*vect_min_y(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3)
{
	t_matrix	*tmp;

	tmp = MIN(pt1->m[Y] < pt2->m[Y]) ? pt1 : pt2;
	tmp = MIN(pt3->m[Y] < tmp->m[Y]) ? pt3 : tmp;
	return (tmp);
}

t_matrix	*vect_cmp(t_matrix **pt)
{
	t_matrix	*tmp;
	int			tmp_i;
	t_matrix	*tmp_a;
	t_matrix	*tm2_b;

	tmp = vect_max_x(pt[1], pt[2], pt[0]);
	tmp->m[3]++;
	tmp = vect_max_y(pt[1], pt[2], pt[0]);
	tmp->m[3]++;
	tmp = vect_min_x(pt[1], pt[2], pt[0]);
	tmp->m[3]--;
	tmp = vect_min_y(pt[1], pt[2], pt[0]);
	tmp->m[3]--;
	tmp = (pt[1]->m[3] < pt[2]->m[3]) ? 1 : 2;
	tmp_a = (pt[1]->m[3] < pt[2]->m[3]) ? pt[2] : pt[1];
	tmp_b = (tmp->m[3] < pt[0]->m[3]) ? pt[0] : tmp;
	tmp = (tmp->m[3] < pt[0]->m[3]) ? tmp : pt[0];
	//	la on rend le min de la composante 3
	return (tmp);
}

/*
 * 	quite a trier auttan metre la couleur avec
 *	tri avec le produit scalaire
 *	-on range par ordre croissant	
 *	-on chope les differentiel et la size
 *	-on peu aussi les swaper directement avec leur adress
 *
 *
 *
 *	-il faudra un peu modifier le sort_vect et le matrix_swap pour aceuillir
 *	des tableau de vecteur et des tableau de couleur
 * */

void	matrix_swap(t_matrix **pta, t_matix **ptb)
{
	t_matrix	*tmp;

	tmp = *pta;
	*pta = *ptb;
	*ptb = tmp;
}

int		sort_vect(t_matrix ***pt, t_matrix ***col)
{
	t_matrix	*sub;
	t_matrix	*tmp;
	t_matrix	*diff;

	if (!(diff = matrix_init(1, 3))
		|| !(sub = matrix_init(1, 6)))
		return -1;
	matrix_sub_in(*(pt[2]), *(pt[1]), sub);
	diff.m[0] = matrix_dot_product(sub, sub);
	matrix_sub_in(*(pt[0]), *(pt[2]), sub);
	diff.m[1] = matrix_dot_product(sub, sub);
	matrix_sub_in(*(pt[1]), *(pt[0]), sub);
	diff.m[2] = matrix_dot_product(sub, sub);
	if (diff.m[0] <= diff.m[1] && diff.m[0] <= diff.m[2])
		;
	else if (diff.m[1] <= diff.m[0] && diff.m[1] <= diff.m[2])
		matrix_swap(*(pt[0]), *(pt[1]));
	else if (diff.m[2] <= diff.m[1] && diff.m[2] <= diff.m[0])
		matrix_swap(*(pt[0]), *(pt[2]));
	matrix_free(&sub);
	matrix_free(&diff);
}


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
	eq = (t_matrix**)lst_eq(dx >= dy, pt, color); 
	//	la il faut aficher sur la size le reste
}

//	on peu faire un peu comm avec les ligne genre trouver le sens dans le quel
//	les deux point le plus eloigner le sont le plus
//


