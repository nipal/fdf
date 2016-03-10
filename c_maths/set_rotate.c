/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/09 22:17:48 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "c_maths.h"

static t_matrix	*init_xrot_matrix(double thetx)
{
	t_matrix	*r;

	r = matrix_init(4, 4);
	r->m[0] = cos(thetx);
	r->m[1] = -sin(thetx);
	r->m[4] = sin(thetx);
	r->m[5] = cos(thetx);
	r->m[10] = 1;
	r->m[15] = 1;
	return (r);
}

static t_matrix	*init_yrot_matrix(double thety)
{
	t_matrix	*r;

	r = matrix_init(4, 4);
	r->m[0] = cos(thety);
	r->m[2] = sin(thety);
	r->m[5] = 1;
	r->m[8] = -sin(thety);
	r->m[10] = cos(thety);
	r->m[15] = 1;
	return (r);
}

static t_matrix	*init_zrot_matrix(double thetz)
{
	t_matrix	*r;

	r = matrix_init(4, 4);
	r->m[0] = 1;
	r->m[5] = cos(thetz);
	r->m[6] = -sin(thetz);
	r->m[9] = sin(thetz);
	r->m[10] = cos(thetz);
	r->m[15] = 1;
	return (r);
}

t_matrix	*set_rotate(double thetx, double thety, double thetz)
{
	t_matrix	*rx;
	t_matrix	*ry;
	t_matrix	*rz;
	t_matrix	*r;

	rx = init_xrot_matrix(thetx);
	ry = init_yrot_matrix(thety);
	rz = init_zrot_matrix(thetz);
	r = matrix_product(rx, ry);
	matrix_free(&rx);
	free(ry);
	ry = r;
	r = matrix_product(r, rz);
	matrix_free(&ry);
	matrix_free(&rz);
	return (r);
}
/*
 *	supression des leaks potentiel sur avec matrix_free
 *	et le remlloc de matrix product 
 * */
