/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 03:47:02 by fjanoty           #+#    #+#             */
/*   Updated: 2016/04/07 10:48:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

int				eq_solve(t_eq *eq)
{
	double	accuracy;

	accuracy = 30;
	if (eq->dim == 0)
		return(0);
	else if (eq->dim == 1)
		return (eq_solve_deg1(eq));
	else if (eq->dim == 2)
		return (eq_solve_deg2(eq));
	else
		return (eq_solve_degn(eq, accuracy));
}

int				eq_solve_deg1(t_eq *eq)
{
	double	a;
	double	b;

	a = eq->coef->m[1];
	b = eq->coef->m[0];
	if (a == 0)
		return (0);
	eq->nb_roots = 1;
	eq->roots->m[0] = -b / a;
	return (1);
}

int				eq_solve_deg2(t_eq *eq)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = eq->coef->m[2];
	b = eq->coef->m[1];
	c = eq->coef->m[0];
	if (a == 0 && b == 0)
		return (0);
	delta = b * b - 4 * a * c;
	delta = sqrt(delta);
	if (delta < 0)
		return (0);
	eq->nb_roots = 2;
	eq->roots->m[0] = (-b - delta) / (2 * a);
	eq->roots->m[1] = (-b + delta) / (2 * a);
	return (1);
}
