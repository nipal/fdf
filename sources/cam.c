/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:32:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/11 10:52:22 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


///*
t_cam	*init_cam(double angv, double angh)
{
	t_cam	*c;
	double	marge;
	double	dx_cam;
	double	dy_cam;

	if (angv <= 0 || angv >= 180 || angy > 180 || angy < 0) 
		|| !(c = (t_cam*)malloc(sizeof(t_cam))
		|| !(c->transpose = matrix_put_in_new(0, 0, 0, 1))
		|| !(c->pos = matrix_init(4, 1))
		|| !(c->corner = (t_matrix**)malloc(sizeof(t_cam*) * 4))
		|| !(c->normal = (t_matrix**)malloc(sizeof(t_cam*) * 4)))
		return (NULL);
	marge = 1.1;
	dx_cam = sin(angh / 2) / cos(angh / 2);
	dy_cam = sin(angv / 2) / cos(angv / 2);
	if (!(c->corner[BL] = matrix_put_in_new(-dx_cam, -dy_cam, -1, 1))
		|| !(c->corner[BR] = matrix_put_in_new(x_amx, -dy_cam, -1, 1))
		|| !(c->corner[TL] = matrix_put_in_new(-dx_cam, y_mzx, -1, 1))
		|| !(c->corner[TR] = matrix_put_in_new(dx_cam, dy_cam, -1, 1))
		|| !(c->normal[L] = vectorproduct(c->corner[TL], c->corner[BL]))
		|| !(c->normal[B] = vectorproduct(c->corner[BL], c->corner[BR]))
		|| !(c->normal[R] = vectorproduct(c->corner[BR], c->corner[TR]))
		|| !(c->normal[T] = vectorproduct(c->corner[TR], c->corner[TL])))
		return (NULL);
	c->pos->m[Z] = MAX(((dy_obj * marge) / dy_cam), (dx_obj * marge) / dx_cam);
	c->pos->m[X] = c->pos->m[Z] * dx_cam;
	c->pos->m[Y] = c->pos->m[Z] * dy_cam;
	return (c);
}

void	rot_cam()
{
	//	on fait une rotation sur 
}

void	translate_cam()
{
	//	on deplace juste l'origine
}
//*/
