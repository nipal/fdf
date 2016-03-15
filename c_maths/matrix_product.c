/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_product.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/14 03:39:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void	matrix_product_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int		i;
	int		j;
	int		k;
//	double	sum;

	if (!a || !b)
		return ;
	if (a->x != b->y)
		return ;
	j = -1;
//	ft_bzero(c->m, sizeof(double) * b->x * a->y);
	while (++j < c->y)
	{
		i = -1;
		while (++i < c->x)
		{
			k = -1;
			c->m[i + (j * c->x)] = 0;
			while (++k < a->x)
				c->m[i + (j * c->x)] += a->m[k + (j * a->x)] * b->m[i + (k * b->x)];
		}
	}
}

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
	//		c->m[i + (j * c->x)] = 0;
			while (++k < a->x)
				c->m[i + (j * c->x)] += a->m[k + (j * a->x)] * b->m[i + (k * b->x)];
		}
	}
	return (c);
}
