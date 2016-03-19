/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:53:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/19 01:19:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.c"

/*
# define BEG_POS   0
# define DELTA_POS 1
# define BEG_COL   2
# define DELTA_POS 3
*/

void	line_y(t_matrix **mat_line, t_env *env)
{
	static	t_env	*e;

	if (env)
		e = env;
	else if (/*y1 > y2*/)
	else
}

void	line_x(t_env *e, t_matrix *eq, t_matrix *c1, t_matrix *diff_c)
{
	int					i;
	static		t_env	*e;
	t_matrix			*pt1;

	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
	if (eq->[SIZE] >= 0)
	{
		while (++i < eq->[SIZE])
		{
			pt1->m[X] = eq->m[X] + i;
			pt1->m[Y] = eq->m[Y] + (i * eq->m[COEF]);
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > eq->[SIZE])
	{
		pt1->m[X] = eq->m[X] + i;
		pt1->m[Y] = eq->m[Y] - (i * eq->m[COEF]);
		pix_to_img(e, pt1, c1);
		matrix_add_in(c1, diff_c, c1);
	}		
}


void	line_y(t_env *e, t_matrix *eq, t_matrix *c1, t_matrix *diff_c)
{
	int					i;
	static		t_env	*e;
	t_matrix			*pt1;

	i = (eq->m[SIZE] >= 0) ? -1 : 1;
	if ((env && (e = env)) || !(pt1 = matrix_init(1, 4)))
		return ;
	if (eq->[SIZE] >= 0)
	{
		while (++i < eq->[SIZE])
		{
			pt1->m[X] = eq->m[X] + (i * eq->m[COEF]);
			pt1->m[Y] = eq->m[Y] + i;
			pix_to_img(e, pt1, c1);
			matrix_add_in(c1, diff_c, c1);
		}
		return ;
	}
	while (--i > eq->[SIZE])
	{
		pt1->m[X] = eq->m[X] - (i * eq->m[COEF]);
		pt1->m[Y] = eq->m[Y] + i;
		pix_to_img(e, pt1, c1);
		matrix_add_in(c1, diff_c, c1);
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

void	init_matline_opt(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2)
{
	t_matrix			*diff;
	t_matrix			*eq;
	t_matrix			*diff_color;
	int					size;

	if (!(diff = matrix_sub(pt2, pt1))
		|| !(diff_color = matrix_sub(c2, c1))
		|| !(eq = matrix_put_in_new(pt1->m[X], pt1->m[Y], 0, 1)))
		return ;
	if (ABS(diff->m[X]) >= ABS(diff->m[Y]))
	{
		eq->m[SIZE] = diff->m[X];
		eq->m[COEF] = ABS(diff->m[Y] / diff->m[X]); 
		line_x(e, eq, matrix_copy(c1), matrix_scalar_product_new(c1, 1 / ABS(eq->m[COEF])));
	}
	else
	{
		eq->m[SIZE] = diff->m[Y];
		eq->m[COEF] = ABS(diff->m[X] / diff->m[Y]); 
		line_x(e, eq, matrix_copy(c1), matrix_scalar_product_new(c1, 1 / ABS(eq->m[COEF])));
	}
	matrix_free(&diff);
}

void	print_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;


/*
	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| (!(org = matrix_init(6, 1)) && matrix_free(&diff)))
		return ;
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
//	size = (int)(mat_line->m[NORME] + 0.5);
	
	while (++i < size)
	{
		print = matrix_add(org, diff); 
		vectpx_to_img(e, print);
		matrix_free(&org);
		org = print;
	}
//*/

	p
	diff = 
	size = (ABS() > ABS(dy)) ? dx: dy;





	matrix_free(&diff);
	matrix_free(&print);

}


//	diff =  
//	size = (ABS() > ABS(dy)) ? dx: dy;


//		On prend du plus grand (si != 0) on le fait boucler sur sa taille
