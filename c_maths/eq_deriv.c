/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_deriv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:53:39 by fjanoty           #+#    #+#             */
/*   Updated: 2016/04/08 09:57:17 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix		*eq_get_deriv_coef(t_eq *eq)
{
	t_matrix	*coef;
	int			i;

	if (!(coef = matrix_init(1, eq->dim)))
		return (NULL);
	i = 0;
	while (i < eq->dim)
	{

		coef->m[i] = (i + 1) * eq->coef->m[i + 1];
		i++;
	}
	return (coef);
}

t_eq			*eq_derivation(t_eq *eq)
{
	t_eq		*derivate;

	if (!(derivate = eq_init(eq->dim - 1, eq_get_deriv_coef(eq))) || eq->dim == 0)
		return (NULL);
	derivate->prime = eq;
	return (derivate);
}
