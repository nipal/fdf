/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/08 14:56:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"
#include <stdio.h>

t_matrix	*matrix_init(int x, int y)
{
	t_matrix	*mat;
	double		*m;
	int		i;
	int		j;

	
	dprintf(1, "matrix init: x:%d y:%d\n", x, y);
	if (!(mat = malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(m = malloc(sizeof(double) * x * y)))
		return (NULL);
	mat->x = x;
	mat->y = y;
	mat->m = m;
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			mat->m[i + j * x] = 0;
			j++;
		}
		i++;
	}
	return (mat);
}
