/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:45:58 by fjanoty           #+#    #+#             */
/*   Updated: 2016/04/08 16:42:52 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

double			power(double nb, int pow)
{
	double	result;

	if (pow == 0)
		return (1);
	else if (pow % 2 == 0)
	{
		result = power(nb, pow);
		return (result * result);
	}
	else
		return (nb * power(nb, pow - 1));
}

double			polynome_at(t_eq *eq, double x)
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

double			dicothomy(t_eq *eq, double begin, double end, int acuracy)
{
	double	midle;
	double	signe;
	int		i;

	i = 0;
	signe = polynome_at(eq, begin);
	midle = (begin + end) / 2;
	while (i < acuracy)
	{
		if ((polynome_at(eq, midle) * signe) > 0)
			end = midle;
		else
			begin = midle;
		midle = (begin + end) / 2;
		i++;
	}
	return (midle);
}

//	find_begin	:	determine le premier interval
//	find_next	:	determine l'interval suivant en fonction de la racine a la quele on est
//						ET donne la racine sur laquelle il c'est arreter
//	donne le nombre d'intervalle viable donc le nombre de racine
//	==>	si next roots est a -1 alors c'est la fin


//	on cherche le premier x vers -inf qui inverse le sens en doublan l'interval a chaque fois
double			find_before(t_eq *eq, double x)
{
	double	interval;
	double	y_begin;

	interval = 1;
	y_begin = polynome_at(eq, x);
	while ((polynome_at(eq, x) * y_begin) > 0)
	{
		x -= interval;
		interval *= 2;
	}
	return (x);
}

//	on cherche le premier x vers +inf qui inverse le sens en doublan l'interval a chaque fois
double			find_after(t_eq *eq, double x)
{
	double	interval;
	double	y_begin;

	interval = 1;
	y_begin = polynome_at(eq, x);
	while ((polynome_at(eq, x) * y_begin) > 0)
	{
		x += interval;
		interval *= 2;
	}
	return (x);
}

//	on donne
double			find_next_limit(t_eq *eq, int *root)
{
	double	begin;
	double	x;
	double	y;

	x = eq->derivate->roots->m[*root];
	begin = polynome_at(eq, x);
	y = begin;
	(*root)++;
	while (*root < eq->derivate->nb_roots && (y * begin) > 0)
	{
		x = eq->derivate->roots->m[*root];
		y = polynome_at(eq, x);
		(*root)++;
	}
	if ((y * begin) < 0)
		return (x);
	y = polynome_at(eq->derivate, x + 1);
	if ((y * begin) > 0)
	{
		*root = -1;
		return (0);
	}
	else
		return (find_after(eq, x));
}

double			find_first_limit(t_eq *eq, int *roots)
{
	double	x;
	double	yf;
	double	yfp;

	x = eq->derivate->roots->m[0];
	yf = polynome_at(eq, x);
	yfp = polynome_at(eq->derivate, x - 1);
	if (eq->derivate->nb_roots == 0)
		return (((yf * yfp) > 0) ? find_before(eq, 0) : find_after(eq, 0));
	else if (yf == 0)
	{
		(*roots)++;
		return (x);
	}
	return (((yf * yfp) > 0) ? find_before(eq, 0 ) : find_next_limit(eq, roots));
}

t_matrix		*define_interval(t_eq *eq)
{
	int			i;
	t_matrix	*interval;

	if (!(interval = matrix_init(1, eq->dim + 1)))
		return (NULL);
	i = 0;
	interval->m[eq->nb_roots] = find_first_limit(eq, &i);
	eq->nb_roots += (i >= 0) ? 1 : 0;
	if (i < 0)
		return (NULL);
	while (i >= 0)
	{
		interval->m[(eq->nb_roots)] = find_next_limit(eq, &i);
		eq->nb_roots += (i >= 0) ? 1 : 0;
	}
	return (eq->coef);
}

int				eq_solve_degn(t_eq *eq, int accuracy)
{
	t_matrix	*inter;
	int			i;

	dprintf(1, "deg:%d\n", eq->dim);
	eq_solve(eq->derivate);
	inter = define_interval(eq);
	i = 0;
	while (i < inter->y)
	{
		eq->roots->m[i] = dicothomy(eq, inter->m[i], inter->m[i + 1], accuracy);
		i++;
	}
	if ((eq->nb_roots = inter->y))
		return (1);
	return (0);
}

/*
determiner les interval

si pas de racine on par de zero

premier:	-on part de la premier racine de la derive
				-si f(x0') * f'(x0') > 0 (mm signe)
					{premier racine est avant}
					-tan que (f(x) * f'(x) > 0)
						x = xo' - pow(2, i)
						i++
					begin = x
					end   = x0'

				-sinon
					begin = x0'
					end   = get_next_limite();

		
*/

int				eq_solve_deg3(t_eq *eq);
int				eq_solve_deg4(t_eq *eq);
