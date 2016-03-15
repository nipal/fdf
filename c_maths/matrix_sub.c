/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 02:19:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/15 03:09:41 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void		matrix_sub_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int			i;
	int			size;

	if (!a || !b || !c)
		return ;
	if (a->x != b->x || a->y != b->y)
		return ;
	c->x = a->x;
	c->y = a->y;
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] - b->m[i];
		i++;
	}
}

t_matrix	*matrix_sub(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			size;

	if (!a || !b)
		return (NULL);
	if (a->x != b->x || a->y != b->y)
		return (NULL);
	c = matrix_init(a->x, a->y);
	c->x = a->x;
	c->y = a->y;
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] - b->m[i];
		i++;
	}
	return (c);
}
