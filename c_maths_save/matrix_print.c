/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 16:35:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/08 16:51:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void	matrix_print(t_matrix *mat)
{
	int	i;
	int	j;

	j = 0;
	while (j < mat->y)
	{
		i = 0;
		while (i < mat->x)
		{
			dprintf(1, "[%d][%d] = %f", j, i, mat->m[j * mat->x + i]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
}

void	matrix_print2(t_matrix *mat, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			dprintf(1, "[%d][%d] = %f", j, i, mat->m[j * mat->x + i]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
}
