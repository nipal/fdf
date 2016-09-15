/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 00:32:54 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/14 01:24:14 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*vect_new_vert(double *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(1, size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = tab[i];
		i++;
	}
	return (vect);
}

t_matrix	*vect_new_horz(double *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(size, 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = tab[i];
		i++;
	}
	return (vect);
}

t_matrix	*vect_new_verti(int *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(1, size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = (double)tab[i];
		i++;
	}
	return (vect);
}

t_matrix	*vect_new_horzi(int *tab, int size)
{
	int			i;
	t_matrix	*vect;

	if (!(vect = matrix_init(size, 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		vect->m[i] = (double)tab[i];
		i++;
	}
	return (vect);
}
