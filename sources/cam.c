/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:32:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/12 12:54:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_windir(t_matrix **corner, double fov_x, double fov_y)
{
	int		i;
	double	dx_cam;
	double	dy_cam;
	int		coefy;
	int		coefx;

	if (fov_y <= 0 || fov_y >= 180 || fov_y > 180 || fov_y < 0
		|| !corner || !*corner) 
		return ;
	dx_cam = tan(fov_x / 2);
	dy_cam = tan(fov_y / 2);
	i = 0;
	while (i < 4 && corner[i])
	{
		matrix_buffer(corner[i]);
		coefy = (i % 2) ? 1 : -1;
		coefx = (i > 2) ? 1 : -1;
		matrix_put_in(coefx * dx_cam, coefy * dy_cam, 1, 1);
		i++;
	}	
}

void	set_normal(t_matrix **normal, t_matrix **corner)
{
	int	i;

	if (normal && corner && corner[0])
		return ;
	i = 0;
	while (i < 4 && corner[i + 1] && normal[i])
	{
		vector_product_in(corner[i], corner[(i + 1) % 4], normal[i]);
		i++;
	}
}

int		malloc_cam_tab(t_cam *cam)
{
	int	i;

	i = 0;
	if (!cam || !cam->corner || !cam->normal)
		return 0;
	while (i < 4)
	{
		if (!(cam->corner[i] = matrix_init(4, 1))
			|| !(cam->normal[i] = matrix_init(4, 1)))
			return 0;
		i++;
	}
	return (1);
}

t_cam	*init_cam(double fov_y, double fov_x, int size_x, int size_y)
{
	t_cam	*c;
	double	marge;
	double	dx_cam;
	double	dy_cam;

	c = (t_cam*) malloc(sizeof(t_cam));
	if ((!c || fov_y <= 0 || fov_y >= 180 || fov_y > 180 || fov_y < 0 
		|| !(c->dir = matrix_put_in_new(0, 0, 1, 1))
		|| !(c->rot = matrix_put_in_new(0, 0, 0, 1))
		|| !(c->pos = matrix_put_in_new(0, 0, 0, 1))
		|| !(c->corner = (t_matrix**)malloc(sizeof(t_cam*) * 4))
		|| !(c->normal = (t_matrix**)malloc(sizeof(t_cam*) * 4)))
		|| !(malloc_cam_tab(c)))
		return (NULL);
	set_windir(c->corner, fov_x, fov_y);
	set_normal(c->normal, c->corner);
	marge = 1.1;
	dx_cam = tan(fov_x / 2);
	dy_cam = tan(fov_y / 2);
	c->pos->m[Z] = -MAX(((size_y * marge) / dy_cam), (size_x * marge) / dx_cam);
	return (c);
}

void	rot_cam(t_cam *cam, t_matrix *rot)
{
	t_matrix	*rotation;

	if (!cam || !rot)
		return ;
	matrix_buffer(cam->dir);
	matrix_put_in(0, 0, 1, 1);
	ft_memmove(cam->rot->m, rot->m, sizeof(double) * 3);
	rotation = set_rotate(rot->m[X], rot->m[Y], rot->m[Z]);
	matrix_product_in(cam->dir, rotation, cam->dir);
	matrix_free(&rotation);
}

void	translate_cam(t_cam *cam, t_matrix *pos)
{
	if (!cam || !pos)
		return ;
	ft_memmove(cam->pos->m, pos->m, sizeof(double) * 3);
}
