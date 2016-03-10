/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_put_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 20:07:17 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/09 22:42:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

void	matrix_put_in(double a, double b, double c, double d)
{
	t_matrix	*mat;

	if (!(mat = matrix_buffer(NULL)))
		return ;
	mat->m[0] = a;
	mat->m[1] = b;
	mat->m[2] = c;
	mat->m[3] = d;
}
