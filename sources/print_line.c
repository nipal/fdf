/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/22 18:47:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
# define BEG_POS   0
# define DELTA_POS 1
# define BEG_COL   2
# define DELTA_POS 3
*/

/*
void	line_y(t_matrix **mat_line, t_env *env)
{
	static	t_env	*e;

	if (env)
		e = env;
	else if ()
	else
}
*/

void	line_x(t_env *env, t_matrix *eq, t_matrix *c1, t_matrix *diff_c)
{
	int					i;
	static		t_env	*e = NULL;
	t_matrix			*pt1;

	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
dprintf(1, "eq:\n");
matrix_display(eq);
dprintf(1, "c1:\n");
matrix_display(c1);
dprintf(1, "diff_c:\n");
matrix_display(diff_c);
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if (eq->m[SIZE] >= 0)
	{
		dprintf(1, "bcl ++	size:%f\n", eq->m[SIZE]);
		dprintf(1, "e:%ld\n", (long)e);
		while (++i < (int)eq->m[SIZE])
		{
//			dprintf(1, "i:%d\n", i);
			pt1->m[X] = eq->m[X] + i;
			pt1->m[Y] = eq->m[Y] + (i * eq->m[COEF]);
			pix_to_img(e, pt1, c1);
			c1 = matrix_add(c1, diff_c);
		}
		return ;
	}
	dprintf(1, "bcl --\n size:%f", eq->m[SIZE]);
	while (--i > eq->m[SIZE])
	{
		dprintf(1, "i:%d\n", i);
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


	if ((env && (e = env)))
		return ;
	if (!(pt1 = matrix_init(1, 4)))
		return ;

	if ((!env))
		;//dprintf(1, "no env\n");
	if ((!e))
		;//dprintf(1, "no e\n");
	if ((!eq))
		;//dprintf(1, "no eq\n");
	if ((!c1))
		;//dprintf(1, "no c1\n");
	if ((!diff_c))
		;//dprintf(1, "no diff_c\n");


	;//dprintf(1, "ouiiiii\n");
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	;//dprintf(1, "ouiiiii2\n");
	if (eq->m[SIZE] >= 0)
	{
	;//dprintf(1, "ouiiiii3\n");
		while (++i < eq->m[SIZE])
		{
	;//dprintf(1, "ouiiiii:%d\n", i);
			pt1->m[X] = eq->m[X] + (i * eq->m[COEF]);
			pt1->m[Y] = eq->m[Y] + i;
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > eq->m[SIZE])
	{
		;//dprintf(1, "oukala1:%d\n", i);
		pt1->m[X] = eq->m[X] - (i * eq->m[COEF]);
		;//dprintf(1, "oukala2:%d\n", i);
		pt1->m[Y] = eq->m[Y] + i;
		;//dprintf(1, "oukala3:%d\n", i);
		pix_to_img(e, pt1, c1);
		;//dprintf(1, "oukala4:%d\n", i);
		;//dprintf(1, "diff_c%ld\n", (long)diff_c);
		//matrix_display(diff_c);
		;//dprintf(1, "c1:%ld\n", (long)c1);
//		//matrix_display(c1);
		;//dprintf(1, "oukala5:%d\n", i);
		c1 = matrix_add(c1, diff_c);
		;//dprintf(1, "oukala6:%d\n", i);
	}		
}

/*
	else
	{
		size *= -1;
		while (i > size)
		{
			pt1->m[X] = eq->m[X] + (i * eq->m[COEF]);
			pt1->m[Y] = eq->m[Y] + i;
			i--;
		}		
	}
*/

/*
 *	matline
 * */

void	print_line(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2)
{
	t_matrix			*diff;
	t_matrix			*eq;
	t_matrix			*diff_color;
	static	int	debug = 0;
//	int					size;

//usleep(100000);
dprintf(1, "begin_line%d\n", debug);
	if (!(diff = matrix_sub(pt2, pt1))
		|| !(diff_color = matrix_sub(c2, c1))
		|| !(eq = matrix_put_in_new(pt1->m[X], pt1->m[Y], 0, 1)))
		return ;
//usleep(100000);
dprintf(1, "DIFF:%f\n", ABS(diff->m[X]) - ABS(diff->m[Y]));
dprintf(1, "DX:%f	DY:%f\n", ABS(diff->m[X]), ABS(diff->m[Y]));
dprintf(1, "DX:%f	DY:%f\n", diff->m[X], diff->m[Y]);
dprintf(1, "DIFF color\n");
matrix_display(diff_color);
	if (ABS(diff->m[X]) >= ABS(diff->m[Y]))
	{
		eq->m[SIZE] = diff->m[X];
		//eq->m[COEF] = ABS(diff->m[Y] / diff->m[X]); 
		eq->m[COEF] = diff->m[Y] / diff->m[X]; 
		line_x(0, eq, matrix_copy(c1), matrix_scalar_product_new(diff_color, 1.0 / -eq->m[SIZE]));
	}
	else
	{
		eq->m[SIZE] = diff->m[Y];
		eq->m[COEF] = diff->m[X] / -diff->m[Y]; 
	//`	eq->m[COEF] = ABS(diff->m[X] / diff->m[Y]); 
		line_y(0, eq, matrix_copy(c1), matrix_scalar_product_new(diff_color, 1.0 / eq->m[SIZE]));
	}
dprintf(1, "end_line%d\n", debug++);
	matrix_free(&diff);
}
