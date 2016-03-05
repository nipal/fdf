/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 09:57:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/04 11:15:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*vector_product(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;
	
	if (!(a->x == 3 && a->y == 1 && b->x == 3 && b->y == 1))
		return (NULL);
	if (!(result = matrix_init(3, 1)))
		return (NULL);
	result->m[0] = a->m[1] * b->m[2] - a->m[2] * b->m[1];
	result->m[1] = a->m[2] * b->m[0] - a->m[0] * b->m[2];
	result->m[2] = a->m[0] * b->m[1] - a->m[1] * b->m[0];
	return (result);
}
