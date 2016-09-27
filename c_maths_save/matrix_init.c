/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/17 15:11:19 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"
#include <stdio.h>

t_matrix	*matrix_init(int x, int y)
{
	t_matrix	*mat;
	double		*m;
	int		i;
	int		max;

	
	//dprintf(1, "matrix init: x:%d y:%d\n", x, y);
	max = x * y;
	if (!(mat = (t_matrix*)malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(m = (double*)malloc(sizeof(double) * max)))
		return (NULL);
	mat->x = x;
	mat->y = y;
	mat->m = m;
	i = 0;
	while (i < max)
	{
		mat->m[i] = 0;
		i++;
	}
	return (mat);
}
