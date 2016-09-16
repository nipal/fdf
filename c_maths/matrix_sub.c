/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 02:19:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/16 10:44:25 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void		matrix_sub_in(t_matrix *a, t_matrix *b, t_matrix *c)
{
	int			i;
	int			size;

	if (!a || !b || !c)
	{
		dprintf(1, "error on existence\n");
	   	return ;
	}
	if (a->x != b->x || a->y != b->y || c->x != a->x || c->y != a->y)
	{
		dprintf(1, "error on size	--> ");
		dprintf(1, "Ax:%d Ay:%d Bx:%d By:%d Cx:%d Cy:%d \n", a->x, a->y, b->x, b->y, c->x, c->y);
   		return ;
	}
//	c->x = a->x;
//	c->y = a->y;
	size = c->x * c->y;
//	dprintf(1, "[%d] ", size);
	i = 0;
	while (i < size)
	{
//		dprintf(1, " <bouya> ");
//	dprintf(1, "[ %.1f -", a->m[i]);
//	dprintf(1, " %.1f =", b->m[i]);
		c->m[i] = a->m[i] - b->m[i];
//	dprintf(1, " %.1f]	", c->m[i]);
		i++;
	}
}

t_matrix	*matrix_sub(t_matrix *a, t_matrix *b)
{
	t_matrix	*c;
	int			i;
	int			size;

	if (!a || !b)
	{
		dprintf(1, "error on existence\n");
		return (NULL);
	}
	if (a->x != b->x || a->y != b->y)
	{
		dprintf(1, "error on size	--> ");
		dprintf(1, "Ax:%d Ay:%d Bx:%d By:%d \n", a->x, a->y, b->x, b->y);
		return (NULL);
	}
	c = matrix_init(a->x, a->y);
//	c->x = a->x;
//	c->y = a->y;
	size = c->x * c->y;
	i = 0;
	while (i < size)
	{
		c->m[i] = a->m[i] - b->m[i];
		i++;
	}
	return (c);
}
