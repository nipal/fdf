/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 03:44:17 by fjanoty           #+#    #+#             */
/*   Updated: 2016/04/07 03:44:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void			eq_print_coef(t_eq *eq)
{
	int	i;

	i = eq->dim;
	while (i >= 0)
	{
		dprintf(1, "%f X^%d	", eq->coef->m[i], i);
		i--;
	}
	dprintf(1, "\n");
}

void			eq_print_all_deriv(t_eq *eq)
{
	t_eq	*deriv;
	int		i;

	dprintf(1, "f'{0}	:");
	eq_print_coef(eq);
	deriv = eq->derivate;
	i = 1;
	while (deriv)
	{
		dprintf(1, "f'{%d}	:", i);
		eq_print_coef(deriv);
		deriv = deriv->derivate;
		i++;
	}
}


void			eq_print_roots(t_eq *eq)
{
	int	i;

	i = 0;
	while (i < eq->nb_roots)
	{
		dprintf(1, "x[%d] = %f", i, eq->roots->m[i]);
		i++;
	}
	dprintf(1, "\n");
}
