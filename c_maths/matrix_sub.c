/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 02:19:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/08 02:21:56 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_matrix	*matrix_sub(t_matrix *mat1, t_matrix *mat_2)
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
			c->m[i + j * c->x] = a->m[i + j * c->x] - b->m[i + j * c->x];
			j++;
		}
		i++;
	}
}
