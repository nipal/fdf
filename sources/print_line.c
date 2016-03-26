/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/25 01:38:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
# define BEG_POS   0
# define DELTA_POS 1
# define BEG_COL   2
# define DELTA_POS 3
*/

void	line_x(t_env *env, t_matrix *eq, t_matrix *c1, t_matrix *diff_c)
{
	int					i;
	static		t_env	*e = NULL;
	t_matrix			*pt1;

	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if (eq->m[SIZE] >= 0)
	{
		while (++i < (int)eq->m[SIZE])
		{
			pt1->m[X] = eq->m[X] + i;
			pt1->m[Y] = eq->m[Y] + (i * eq->m[COEF]);
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > -eq->m[SIZE])
	{
		pt1->m[X] = eq->m[X] + i;
		pt1->m[Y] = eq->m[Y] - (i * eq->m[COEF]);
		pix_to_img(e, pt1, c1);
		matrix_add_in(c1, diff_c, c1);
	}		
}


void	line_y(t_env *env, t_matrix *eq, t_matrix *c1, t_matrix *diff_c)
{
	int					i;
	static		t_env	*e = NULL;
	t_matrix			*pt1;

	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if (eq->m[SIZE] >= 0)
	{
		while (++i < eq->m[SIZE])
		{
			pt1->m[X] = eq->m[X] + (i * eq->m[COEF]);
			pt1->m[Y] = eq->m[Y] + i;
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > -eq->m[SIZE])
	{
		pt1->m[X] = eq->m[X] - (i * eq->m[COEF]);
		pt1->m[Y] = eq->m[Y] + i;
		pix_to_img(e, pt1, c1);
		matrix_add_in(c1, diff_c, c1);
	}		
}

void	print_line(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2)
{
	t_matrix			*diff;
	t_matrix			*eq;
	t_matrix			*diff_color;

	if (!(diff = matrix_sub(pt2, pt1))
		|| !(diff_color = matrix_sub(c2, c1))
		|| !(eq = matrix_put_in_new(pt1->m[X], pt1->m[Y], 0, 1)))
		return ;
	if (ABS(diff->m[X]) >= ABS(diff->m[Y]))
	{
		eq->m[SIZE] = diff->m[X];
		eq->m[COEF] = (diff->m[X] < 0) ? diff->m[Y] / -diff->m[X] : diff->m[Y] / diff->m[X];
		(diff->m[X] < 0) ? matrix_scalar_product(diff_color, 1.0 / -eq->m[SIZE])
						 : matrix_scalar_product(diff_color, 1.0 / eq->m[SIZE]); 
		line_x(0, eq, matrix_copy(c1), diff_color);
	}
	else
	{
		eq->m[SIZE] = diff->m[Y];
		eq->m[COEF] = (diff->m[Y] < 0) ? diff->m[X] / -diff->m[Y] : diff->m[X] / diff->m[Y];
		(diff->m[Y] < 0) ? matrix_scalar_product(diff_color, 1.0 / -eq->m[SIZE])
						 : matrix_scalar_product(diff_color, 1.0 / eq->m[SIZE]); 
		line_y(0, eq, matrix_copy(c1), diff_color);
	}
	//matrix_free(&diff);
}
