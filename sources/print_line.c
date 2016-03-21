/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/21 10:47:34 by fjanoty          ###   ########.fr       */
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
	static		t_env	*e;
	t_matrix			*pt1;

	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if (eq->m[SIZE] >= 0)
	{
		while (++i < eq->m[SIZE])
		{
			pt1->m[X] = eq->m[X] + i;
			pt1->m[Y] = eq->m[Y] + (i * eq->m[COEF]);
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > eq->m[SIZE])
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


	if ((env && (e = env)))
		return ;
	if (!(pt1 = matrix_init(1, 4)))
		return ;

	if ((!env))
		dprintf(1, "no env\n");
	if ((!e))
		dprintf(1, "no e\n");
	if ((!eq))
		dprintf(1, "no eq\n");
	if ((!c1))
		dprintf(1, "no c1\n");
	if ((!diff_c))
		dprintf(1, "no diff_c\n");


	dprintf(1, "ouiiiii\n");
	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	dprintf(1, "ouiiiii2\n");
	if (eq->m[SIZE] >= 0)
	{
	dprintf(1, "ouiiiii3\n");
		while (++i < eq->m[SIZE])
		{
	dprintf(1, "ouiiiii:%d\n", i);
			pt1->m[X] = eq->m[X] + (i * eq->m[COEF]);
			pt1->m[Y] = eq->m[Y] + i;
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > eq->m[SIZE])
	{
		dprintf(1, "oukala1:%d\n", i);
		pt1->m[X] = eq->m[X] - (i * eq->m[COEF]);
		dprintf(1, "oukala2:%d\n", i);
		pt1->m[Y] = eq->m[Y] + i;
		dprintf(1, "oukala3:%d\n", i);
		pix_to_img(e, pt1, c1);
		dprintf(1, "oukala4:%d\n", i);
		dprintf(1, "diff_c%ld\n", (long)diff_c);
		matrix_display(diff_c);
		dprintf(1, "c1:%ld\n", (long)c1);
		matrix_display(c1);
		matrix_add_in(c1, diff_c, c1);
		dprintf(1, "oukala5:%d\n", i);
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
//	int					size;

//usleep(100000);
dprintf(1, "pt1:\n");
matrix_display(pt1);
dprintf(1, "c1:\n");
matrix_display(c1);
dprintf(1, "pt2:\n");
matrix_display(pt2);
dprintf(1, "c2:\n");
matrix_display(c2);
dprintf(1, "printlin1\n");
	if (!(diff = matrix_sub(pt2, pt1))
		|| !(diff_color = matrix_sub(c2, c1))
		|| !(eq = matrix_put_in_new(pt1->m[X], pt1->m[Y], 0, 1)))
		return ;
//usleep(100000);
dprintf(1, "printlin2\n");
	if (ABS(diff->m[X]) >= ABS(diff->m[Y]))
	{
dprintf(1, "printline2(A0)\n");
		eq->m[SIZE] = diff->m[X];
dprintf(1, "printline2(A1)\n");
		eq->m[COEF] = ABS(diff->m[Y] / diff->m[X]); 
dprintf(1, "printline2(A2)\n");
		line_x(0, eq, matrix_copy(c1), matrix_scalar_product_new(c1, 1 / ABS(eq->m[COEF])));
dprintf(1, "printline2(A3)\n");
	}
	else
	{
dprintf(1, "printline2(B0)\n");
		eq->m[SIZE] = diff->m[Y];
dprintf(1, "printline2(B1)\n");
		eq->m[COEF] = ABS(diff->m[X] / diff->m[Y]); 
dprintf(1, "printline2(B2)\n");
		line_y(0, eq, matrix_copy(c1), matrix_scalar_product_new(c1, 1 / ABS(eq->m[COEF])));
dprintf(1, "printline2(B3)\n");
	}
//usleep(100000);
dprintf(1, "printline3\n");
	matrix_free(&diff);
}


/*
void	print_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

	diff = ;
	size = (ABS() > ABS(dy)) ? dx: dy;





	matrix_free(&diff);
	matrix_free(&print);

}
*/

//	diff =  
//	size = (ABS() > ABS(dy)) ? dx: dy;


//		On prend du plus grand (si != 0) on le fait boucler sur sa taille
