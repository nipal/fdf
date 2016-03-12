/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 09:57:43 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/12 06:55:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void		vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result)
{
	if (!a || !b || !result)
		return ;
	if (MIN(a->x * a->y, b->x * b->y) < 3)
		return ;
	result->m[0] = a->m[1] * b->m[2] - a->m[2] * b->m[1];
	result->m[1] = a->m[2] * b->m[0] - a->m[0] * b->m[2];
	result->m[2] = a->m[0] * b->m[1] - a->m[1] * b->m[0];
}

t_matrix	*vector_product_s(t_matrix *a, t_matrix *b, int x, int y)
{
	t_matrix	*result;
	
	if (!a || !b || x * y < 3 || x < 0)
		return (NULL);
	if (MIN(a->x * a->y, b->x * b->y) < 3
		|| !(result = matrix_init(x, y)))
		return (NULL);
	vector_product_in(a, b, result);
	return (result);
}

t_matrix	*vector_product(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;
	
	if (!a || !b)
		return (NULL);
	if (MIN(a->x * a->y, b->x * b->y) < 3
		|| !(result = matrix_init(3, 1)))
		return (NULL);
	vector_product_in(a, b, result);
	return (result);
}
