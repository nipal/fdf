/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_product.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/02 00:04:57 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_product(t_matrix *a, t_matrix *b)
{
	int		i;
	int		j;
	int		k;
	t_matrix	*c;

	if (!a || !b)
		return (NULL);
	if (a->x != b->y)
		return (NULL);
	if (!(c = matrix_init(b->x, a->y)))
		return (NULL);
	j = -1;
	while (++j < c->y)
	{
		i = -1;
		while (++i < c->x)
		{
			k = -1;
			while (++k < a->x)
				c->m[i + j * c->x] += a->m[k + j * a->x] * b->m[i + k * b->x];
		}
	}
	return (c);
}
