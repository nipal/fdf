/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/25 01:38:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "c_maths.h"
/*	si non on fait tout simple,
 *	- on relis le premier au deuxieme et au troisieme
 *	
 * */

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2);
double	maximum(double a, double b, double c, double d)
{
	double	max;

	max = MAX(ABS(a), ABS(b));
	max = MAX(max, ABS(c));
	max = MAX(max, ABS(d));
	return (max + 10);
}

t_matrix	**tab_matrix(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3)
{
	t_matrix	**tab;

	if (!(tab = (t_matrix**) malloc(sizeof(t_matrix*) * 3)))
	{
		dprintf(1, "error matrix init\n");
		return (NULL);
	}
	tab[0] = matrix_copy(pt1);
	tab[1] = matrix_copy(pt2);
	tab[2] = matrix_copy(pt3);
	return (tab);
}

void	print_triangle(t_env *e, t_matrix **pt, t_matrix **cl)
{
	t_matrix	*eq_p1;
	t_matrix	*eq_p2;
	t_matrix	*diff_p1;
	t_matrix	*diff_p2;
	t_matrix	*eq_c1;
	t_matrix	*eq_c2;
	t_matrix	*diff_c1;
	t_matrix	*diff_c2;

	t_matrix	*color;
	double		size;
	int			i;

	diff_c1 = NULL;
	diff_c2 = NULL;
	(void)cl;
	(void)e;
	color = matrix_put_in_new(70, 90, 90, 0);;

	diff_p1 = matrix_sub(pt[1], pt[0]);
	diff_p2 = matrix_sub(pt[2], pt[0]);
	size = maximum(diff_p1->m[X], diff_p1->m[Y], diff_p2->m[X], diff_p2->m[Y]);


	dprintf(1, "--------------------------\n");
	matrix_display(pt[0]);
	dprintf(1, "::\n");
	matrix_display(pt[1]);
	dprintf(1, "::\n");
	matrix_display(pt[2]);
	dprintf(1, "dp1x:%f\n", diff_p1->m[X]);
	dprintf(1, "dp1y:%f\n", diff_p1->m[Y]);
	dprintf(1, "dp2x:%f\n", diff_p2->m[X]);
	dprintf(1, "dp2y:%f\n", diff_p2->m[Y]);
	dprintf(1, "--------------------------\n");


	matrix_scalar_product(diff_p1, 1 / size);
	matrix_scalar_product(diff_p2, 1 / size);
	eq_p1 = matrix_put_in_new(pt[0]->m[X], pt[0]->m[Y], pt[0]->m[Z], 0);
	eq_p2 = matrix_put_in_new(pt[0]->m[X], pt[0]->m[Y], pt[0]->m[Z], 0);

	diff_c1 = matrix_sub(cl[1], cl[0]);
	diff_c2 = matrix_sub(cl[2], cl[0]);
	matrix_scalar_product(diff_c1, 1 / size);
	matrix_scalar_product(diff_c2, 1 / size);
	eq_c1 = matrix_put_in_new(cl[0]->m[R], cl[0]->m[G], cl[0]->m[B], 0);
	eq_c2 = matrix_put_in_new(cl[0]->m[R], cl[0]->m[G], cl[0]->m[B], 0);

	i = 0;
	while (i < size)
	{

//		dprintf(1, "i:%d	size:%f\n", i, size);
		matrix_add_in(eq_p1, diff_p1, eq_p1);
		matrix_add_in(eq_p2, diff_p2, eq_p2);

		eq_c1 = matrix_add(eq_c1, diff_c1);
		eq_c2 = matrix_add(eq_c2, diff_c2);

		print_line(matrix_copy(eq_p1), matrix_copy(eq_c1), matrix_copy(eq_p2), matrix_copy(eq_c2));

		i++;
	}
}
