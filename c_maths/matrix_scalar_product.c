/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scalar_product.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/02 00:29:36 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_scalar_product(t_matrix *a, double d)
{
	int		i;
	int		j;
	t_matrix	*b;

	if (!a || !d)
		return (NULL);
	if (!(b = matrix_init(a->x, a->y)))
		return (NULL);
	j = -1;
	while (++j < b->y)
	{
		i = -1;
		while (++i < b->x)
				b->m[i + j * b->x] += a->m[i + j * a->x] * d;
	}
	return (b);
}
