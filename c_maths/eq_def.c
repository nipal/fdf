/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:45:17 by fjanoty           #+#    #+#             */
/*   Updated: 2016/04/08 09:34:07 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_eq			*eq_init(int dim, t_matrix *coef)
{
	t_eq		*eq;
	t_matrix	*roots;

	dprintf(1, "init:%d\n", dim);
	if (!(eq = (t_eq*)malloc(sizeof(t_eq)))
		|| !(roots = matrix_init(1, eq->dim)))
		return (NULL);
	eq->dim = dim;
	eq->coef = coef;
	eq->prime = NULL;
	eq->roots = roots;
	eq->nb_roots = 0;
	eq->derivate = (dim > 0) ? eq_derivation(eq) : NULL;
	return (eq);
}

t_eq			*eq_creat(int dim)
{
	t_eq		*eq;
	t_matrix	*coef;
	t_matrix	*roots;

	if (!(eq = (t_eq*)malloc(sizeof(t_eq)))
		|| !(coef = matrix_init(1, dim + 1))
		|| !(roots = matrix_init(1, eq->dim)))
		return (NULL);
	eq->dim = dim;
	eq->coef = coef;
	eq->prime = NULL;
	eq->roots = roots;	
	eq->nb_roots = 0;
	eq->derivate = NULL;
	return (eq);
}
