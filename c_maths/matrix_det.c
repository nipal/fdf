/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_det.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/27 08:07:53 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

double	matrix_det(t_matrix *a)
{
	int		i;
	int		j;
	double	d;

	if (!a)
		return (0);
	d = 0;
	j = -1;
	while (++j < a->y)
	{
		i = -1;
		while (++i < a->x)
		{
			d += a->m[i + j * a->x] * d;
		}
	}
	return (d);
}
