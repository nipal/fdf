/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2014/09/14 00:27:06 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*matrix_init(int x, int y)
{
	t_matrix	*mat;
	double		*m;
	int		i;
	int		j;

	
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
