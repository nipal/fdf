/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dot_product.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2014/09/14 00:27:06 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_add(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int		i;
	int		j;

	if (!a || !b)
		return (NULL);
	if (a->x != b->x || a->y != b->y)
		return (NULL);
	c = matrix_init(a->x, a->y);
	c->x = a->x;
	c->y = a->y;
	i = 0;
	while (i < c->x)
	{
		j = 0;
		while (j < c->y)
		{
			c->m[i + j * c->x] = a->m[i + j * c->x] + b->m[i + j * c->x];
			j++;
		}
		i++;
	}
	return (c);
}
