/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:32:11 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/15 00:26:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	describe_cam(t_cam *cam)
{
	int	i;

	if (!cam)
	{
		dprintf(1, "		NO CAAAAAAMM!!!\n");
	}
	dprintf(1, "Corner\n");
	if (cam->corner)
	{
		i = 0;
		while (i < 4)
		{

			dprintf(1, " corner[%i]", i);
			if (cam)
				;//matrix_display(cam->corner[i]);
			else
				dprintf(1, "NO corner[%d]\n", i);
			i++;
		}
	}
	else
		dprintf(1, "	NO CORNER TAB\n");

	dprintf(1, "normal\n");
	if (cam->normal)
	{
		i = 0;
		while (i < 4)
		{
			dprintf(1, " normal[%i]", i);
			if (cam)
				;//matrix_display(cam->normal[i]);
			else
				dprintf(1, "	NO normal[%d]\n", i);
			i++;
		}
	}
	else
		dprintf(1, "	NO NORMAL TAB\n");

	dprintf(1, "pos\n");
	if (cam->pos)
		;//matrix_display(cam->pos);
	else
		dprintf(1, "	NO POS\n");

	dprintf(1, "dir\n");
	if (cam->dir)
		;//matrix_display(cam->dir);
	else
		dprintf(1, "	NO DIR\n");

	dprintf(1, "rot\n");
	if (cam->rot)
		;//matrix_display(cam->rot);
	else
		dprintf(1, "	NO ROT\n");
//	sleep(10);
}

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
	dx_cam = tan(fov_x);
	dy_cam = tan(fov_y);
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

	if (!(normal))
		dprintf(1 , "NO normal \n");
	else if (!(*normal))
		dprintf(1 , "NO *naormal \n");
	if (!(corner))
		dprintf(1 , "NO  corner\n");
	else if (!(*corner))
		dprintf(1 , "NO *corner \n");
	else if (!(corner[0]))
		dprintf(1 , "NO corner[0] \n");
	if (!normal || !corner || !corner[0])
	{
		dprintf(1, "ERROR INPUT !!!\n");
		return ;
	}
	i = 0;
	while (i < 4 && corner[(i + 1) % 4])
	{
		vector_product_in(corner[i], corner[(i + 1) % 4], normal[i]);
		i++;
	}
//	dprintf(1, "	#####end normal i:%d#####\n", i);
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

t_cam	*init_cam(double fov_y, double fov_x, t_env *e)
{
	t_cam	*c;
	double	marge;
	double	dx_cam;
	double	dy_cam;
	static	double	increm = 0;

	c = (t_cam*) malloc(sizeof(t_cam));
	if ((!c || fov_y <= 0 || fov_y >= 180 || fov_y > 180 || fov_y < 0 
		|| !(c->dir = matrix_put_in_new(0, 0, 1, 1))
		|| !(c->rot = matrix_put_in_new(e->rot_x, e->rot_y, e->rot_z, 1))
		|| !(c->pos = matrix_put_in_new(0, 0, 0, 1))
		|| !(c->corner = (t_matrix**)malloc(sizeof(t_cam*) * 4))
		|| !(c->normal = (t_matrix**)malloc(sizeof(t_cam*) * 4)))
		|| !(malloc_cam_tab(c)))
		return (NULL);
	marge = 1.5;
	dx_cam = tan(fov_x / 2);
	dy_cam = tan(fov_y / 2);
	c->pos->m[Z] = - 170 - MAX(((e->size_map_y * marge) / dy_cam), (e->size_map_x * marge) / dx_cam);
	c->pos->m[X] = 10;
	c->pos->m[Y] = 10;
	set_windir(c->corner, fov_x, fov_y);
	set_normal(c->normal, c->corner);
//	dprintf(1, "YES I AM\n");
//	describe_cam(c);
//	dprintf(1, "YES I AM2\n");
	increm += 0.03;
	return (c);
}

/*
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
*/
