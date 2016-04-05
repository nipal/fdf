/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_eq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 14:35:08 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/24 03:20:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//void	print_line(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2);
#include "fdf.h"

void			print_x_axe(int min, int pos_y, int ecr_x, t_matrix *color)
{
	t_matrix	*p1;
	t_matrix	*p2;
	int	i;
	int	size;
	int	coef;
	int	j;

	coef = 1;
	size = ecr_x;
	j = 1;
	while (coef < size)
	{
		i = 0;
		while (i < size)
		{
			if((ABS(i - min) % coef) == 0)
			{
				p1 = matrix_put_in_new(i, pos_y + (1 * j), 0, 0);
				p2 = matrix_put_in_new(i, pos_y - (1 * j), 0, 0);
				print_line(p1, color, p2, color);
				matrix_free(&p1);
				matrix_free(&p2);
			}
			if((ABS(i - min) % (coef * 5)) == 0)
			{
				p1 = matrix_put_in_new(i, pos_y + (1 * (j + 2)), 0, 0);
				p2 = matrix_put_in_new(i, pos_y - (1 * (j + 2)), 0, 0);
				print_line(p1, color, p2, color);
				matrix_free(&p1);
				matrix_free(&p2);
			}
			i++;
		}
		coef *= 10;
		j += 10;
	}
}

void			print_y_axe(int min, int pos_x, int ecr_y, t_matrix *color)
{
	t_matrix	*p1;
	t_matrix	*p2;
	int	i;
	int	size;
	int	coef;
	int	j;

	coef = 1;
	size = ecr_y;
	j = 1;
	while (coef < (size / 5))
	{
		i = 0;
		while (i < size)
		{
			if((ABS(i - min) % coef) == 0)
			{
				p1 = matrix_put_in_new(pos_x + (1 * j), i, 0, 0);
				p2 = matrix_put_in_new(pos_x - (1 * j), i, 0, 0);
				print_line(p1, color, p2, color);
				matrix_free(&p1);
				matrix_free(&p2);
			}
			if((ABS(i - min) % (coef * 5)) == 0)
			{
				p1 = matrix_put_in_new(pos_x + (1 * (j + 2)), i, 0, 0);
				p2 = matrix_put_in_new(pos_x - (1 * (j + 2)), i, 0, 0);
				print_line(p1, color, p2, color);
				matrix_free(&p1);
				matrix_free(&p2);
			}
			i++;
		}
		coef *= 10;
		j += 7;
	}
}


void			print_repaire(t_matrix *pos, t_matrix *color, t_env *e)
{
	(void)pos;
	(void)color;
	(void)e;
//*
	print_x_axe(pos->m[X], pos->m[X], e->ecr_x, color);
	print_y_axe(pos->m[Y], pos->m[Y], e->ecr_y, color);
//	*/
}

/*
**	on desine sur un interval
*/

double			power(double number, int pow)
{
	double	result;

	if (pow == 0)
		return (1);
	else if (pow % 2 == 0)
	{
		result = power(number, pow / 2);
		return (result * result);
	}
	else
		return (number * power(number, pow - 1));
}

double			func(t_eq *eq, double x)
{
	double	result;
	int		i;

	i = 0;
	result = 0;
	while (i <= eq->dim)
	{
		result += eq->coef->m[i] * power(x, i);
		i++;
	}
	return (result);
}

void			print_eq(t_eq *eq, t_matrix *org, double fact, t_env *e)
{
	t_matrix *p1;
	t_matrix *p2;
	t_matrix *color;
	int		i;
	int		size;
	double	x;
	double	y;

	i = 0;
	size = e->ecr_x;
	color = matrix_put_in_new(200, 200, 200, 0);
	while (i <size)
	{
		x = ((double)(i - org->m[X])) * fact;
		y = -func(eq, x) + org->m[Y];
		p1 = matrix_put_in_new(i, y, 0, 0);

		x = ((double)(i + 1 - org->m[X])) * fact;
		y = -func(eq, x) + org->m[Y];
		p2 = matrix_put_in_new(i + 1, y, 0, 0);
		
		dprintf(1, "p1:\n");
		matrix_display(p1);
		dprintf(1, "p2:\n");
		matrix_display(p2);

		print_line(p1, color, p2, color);
		i++;
		matrix_free(&p1);
		matrix_free(&p2);
	}
//	matrix_free(&color);
}


/*
int				eq_solve_deg1(t_eq *eq)
{
	t_matrix	*roots;

	roots = matrix_init(1, 1);
	roots = -eq->coef->m[0] / eq->ceof->m[1];
	eq->roots = roots;
	return (1);
}

int				eq_solve_deg2(t_eq *eq)
{
	t_matrix	*roots;
	int			nb;
	double		delta;

	nb = 0;
	roots = NULL;
	if ((delta = (eq->coef->[1] * eq->coef->[1]) - 4 * (eq->coef->[0] eq->coef->[2])) >= 0)
	{
		delta = sqrt(delta);
		if (delta == 0)
			nb = 1;
		else
			nb = 2;
		roots = matrix_init(nb, 1);
		roots->m[0] = (-eq->coef[1] - delta) / (2 * eq->coef->m[2])
		if (nb == 2)
			roots->m[1] = (-eq->coef[1] + delta) / (2 * eq->coef->m[2])
	}
	eq->roots = roots;
	return (1);
//	matrix_free(&roots);
}


int				eq_solve_degn(t_eq *eq)
{
	//	on defnie le nombre de zero a partir des la racine de la deriver;
	
}
*/
