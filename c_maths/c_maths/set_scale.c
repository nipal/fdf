/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/03 05:31:40 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"

t_matrix	*set_scale(double sx, double sy, double sz)
{
	t_matrix	*s;

	s = matrix_init(4, 4);
	s->m[0] = sx;
	s->m[5] = sy;
	s->m[10] = sz;
	s->m[15] = 1;
	return (s);
}
