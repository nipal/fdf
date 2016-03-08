/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/08 10:14:37 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	putl(t_env *e, t_point start, t_point end)
{
	(void) e;
	(void) start;
	(void) end;
	/*
	double	dd;
	double	x;
	double	y;
	double	dx;
	double	dy;

	x = start.x;
	y = start.y;
	dx = end.x - start.x;
	dy = end.y - start.y;
	dd = sqrt((dx * dx) + (dy * dy));
	dx = dx / dd;
	dy = dy / dd;
	while (dd-- >= 0)
	{
		if (x < 1440 && x > 0 && y > 0 && y < 900)
//			px_to_img(e, ABS(x), ABS(y));
		x += dx;
		y += dy;
	}
	*/
}

//	si on a un deltax et ddelta y positif
//

int		set_color(double z)
{
	int	color;
	
	z = (z > 255) ?255 - ( z - 255): z;
	z = (z < 0) ? 0 : z;
	color = (int)z << 16 | (int)z << 8 | (int)z;
	return (color);
}

void	draw_vertical_line(t_env *e, t_matrix *pos, double beg_z, double delta_z)
{
	int	i;
	int	y;

	(void)delta_z;
	i = 0;
	if (!(pos->m[Y2] - pos->m[Y1]))
		pos->m[Y2]++;
	dprintf(1, "beg_z:%f delta_z:%f\n", beg_z, delta_z);
	if (pos->m[Y2] > pos->m[Y1])
		while (pos->m[Y1] < pos->m[Y2])
		{
			y = pos->m[Y1];
			if (pos->m[Y1] > pos->m[MAX_Y])
				y = pos->m[MAX_Y];
			if (pos->m[Y1] < pos->m[MIN_Y])
				y = pos->m[MIN_Y];
			px_to_img(e, pos->m[X], y, set_color(beg_z + (i * delta_z)));
			pos->m[Y1]++;
			i++;
		}
	else
		while (pos->m[Y1] > pos->m[Y2])
		{
			y = pos->m[Y1];
			if (pos->m[Y1] < pos->m[MIN_Y])
				y = pos->m[MIN_Y];
			if (pos->m[Y1] > pos->m[MAX_Y])
				y = pos->m[MAX_Y];
			px_to_img(e, pos->m[X], y, set_color(beg_z + (i * delta_z)));
			pos->m[Y1]--;
			i++;
		}
}

int		draw_limit(t_env *e, t_matrix *pt1, t_matrix *pt2)
{
	t_matrix	*pt;
	double		delta_z;

	if (!(pt = matrix_init(6, 1)))
		return (0);
	pt->m[X] = pt1->m[X];
	pt->m[Y1] = pt1->m[Y];
	pt->m[Y2] = pt2->m[Y];
	pt->m[MAX_Y] = MAX(pt1->m[Y], pt2->m[Y]);
	pt->m[MIN_Y] = MIN(pt1->m[Y], pt2->m[Y]);
	delta_z = (pt2->m[Z] - pt1->m[Z]) / (pt2->m[Y] - pt1->m[Y]);
	dprintf(1, "diffz:%f diffy:%f dz:%f\n", (pt2->m[Z] - pt1->m[Z]), (pt2->m[Y] - pt1->m[Y]) , delta_z);
//	draw_vertical_line(e, pt, c->m[BEG_Z], c->m[DELTA_Z] / (v->m[DELTA_Y]));
	draw_vertical_line(e, pt, pt1->m[Z], delta_z);
	free_matrix(pt);
	return (0);
}

void	define_var(t_matrix *var, t_matrix *color, t_matrix *pt1, t_matrix *pt2)
{
	if (pt1->m[X] <= pt1->m[X])
	{
		var->m[BEG_X] = pt1->m[X];
		var->m[END_X] = pt2->m[X];
		var->m[DELTA_Y] = (pt2->m[Y] - pt1->m[Y]) / (pt2->m[X] - pt1->m[X]);
		var->m[BEG_Y] = pt1->m[Y]; 
		color->m[BEG_Z] = pt1->m[Z];
		color->m[DELTA_Z] = (pt2->m[Z] - pt1->m[Z]) / (pt2->m[X] - pt1->m[X]);
	}
	else
	{
		var->m[BEG_X] = pt2->m[X];
		var->m[END_X] = pt1->m[X];
		var->m[DELTA_Y] = (pt1->m[Y] - pt2->m[Y]) / (pt1->m[X] - pt2->m[X]);
		var->m[BEG_Y] = pt2->m[Y]; 
		color->m[BEG_Z] = pt2->m[Z];
		color->m[DELTA_Z] = (pt1->m[Z] - pt2->m[Z]) / (pt1->m[X] - pt2->m[X]);
	}
	if (var->m[DELTA_Z] < 0)
		var->m[DELTA_Z] *= -1;
	if (var->m[DELTA_Y] == 0)
		var->m[DELTA_Y] = 1;
	if ((pt1->m[X] - pt2->m[X]) == 0)
		var->m[DELTA_Z] = -1;
}

void	draw_line(t_env *e, t_matrix *pt1, t_matrix *pt2)
{
	int			i;
	t_matrix	*v;
	t_matrix	*pt;
	t_matrix	*c;

	if ((!(pt1->m[X] - pt2->m[X]) && draw_limit(e, pt1, pt2))
		|| !(pt = matrix_init(6, 1))
		|| (!(v = matrix_init(4, 1)) && free_matrix(pt))
		|| (!(c = matrix_init(2, 1)) && free_matrix(pt) && free_matrix(v)))
		return ;
	pt->m[MAX_Y] = MAX(pt1->m[Y], pt2->m[Y]);
	pt->m[MIN_Y] = MIN(pt1->m[Y], pt2->m[Y]);
	i = (pt1->m[X] > pt2->m[X]) ? 0 : -1;
	define_var(v, c, pt1, pt2);
	px_to_img(e, pt->m[X], pt->m[BEG_Y], 0x00FFFFFF);
	if (pt2->m[X] >= pt1->m[X])
		while (v->m[BEG_X] + ++i <= v->m[END_X])
		{
			pt->m[X] = i + v->m[BEG_X];
			pt->m[Y1] = v->m[BEG_Y] + i * v->m[DELTA_Y]; 
			pt->m[Y2] = v->m[BEG_Y] + (i + 1) * v->m[DELTA_Y]; 
//			printf("beg_z:%f  felta_z:%f\n", c->m[BEG_Z], c->m[DELTA_Z]);
			draw_vertical_line(e, pt, c->m[BEG_Z], c->m[DELTA_Z] / (v->m[DELTA_Y]));
			px_to_img(e, pt2->m[X], pt2->m[Y], 0x00FFFFFF);
			px_to_img(e, pt1->m[X], pt1->m[Y], 0x00FFFFFF);
			c->m[BEG_Z] += c->m[DELTA_Z];
		}
	else if (pt2->m[X] <= pt1->m[X])
		while (v->m[BEG_X] + --i >= v->m[END_X])
		{
			pt->m[X] = i + v->m[BEG_X];
			pt->m[Y1] = v->m[BEG_Y] + i * v->m[DELTA_Y]; 
			pt->m[Y2] = v->m[BEG_Y] + (i + 1) * v->m[DELTA_Y]; 
//			printf("beg_z:%f  felta_z:%f\n", c->m[BEG_Z], c->m[DELTA_Z]);
			draw_vertical_line(e, pt, -c->m[BEG_Z], (c->m[DELTA_Z]) / (v->m[DELTA_Y]));
			px_to_img(e, pt2->m[X], pt2->m[Y], 0x00FFFFFF);
			px_to_img(e, pt1->m[X], pt1->m[Y], 0x0FFFFFFF);
			c->m[BEG_Z] += c->m[DELTA_Z];
		}
	usleep(100000);
	free_matrix(pt);
	free_matrix(c);
	free_matrix(v);
}



void	draw_line2(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| (!(org = matrix_init(6, 1)) && matrix_free(diff)))
		return ;
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size)
	{
		print = matrix_add(org, diff); 
		vectpx_to_img(e, print);
		matrix_free(org);
		org = print;
		i++;
	}
	matrix_free(org);
	matrix_free(diff);
	matrix_free(print);
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2
			, t_matrix *c1, t_matrix *c2)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	if (!(mat_line = matrix_init(13, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| (!(diff = matrix_sub(pt1, pt2)) && free_matrix(mat_line)))
		return (NULL);
	diff->m[Z] = 0;
	norme = sqrt(matrix_dot_product(diff, diff)); 
	mat_line->m[NORME] = norme;
	diff = matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	if ((!(matrix_scalar_product(diff = matrix_sub(c1, c2), 1 / norme)
		&& free_matrix(mat_line))))
		return (NULL);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	return (mat_line);
}

t_matrix	*sqr_rotate(int x, int size)
{
	t_matrix	*pt;
	int			a;
	int			b;
	int			val;

	if (!(pt = matrix_init(4, 1)))
		return (NULL);
	a = x % size == x % (size * 2);
	b = x % (size * 2) == x % (size * 4);
	val = x % size;
	pt->m[2] = 0;
	pt->m[3] = 1;
	if (a && b)
	{
		pt->m[0] = -(size / 2);
		pt->m[1] = val - size / 2;
	}
	else if (!a && b)
	{
		pt->m[0] = val - size / 2;
		pt->m[1] = (size / 2);
	}
	else if (a && !b)
	{
		pt->m[0] = size / 2;
		pt->m[1] = size / 2 - val;
	}
	else if (!a && !b)
	{
		pt->m[0] = size / 2 - val;
		pt->m[1] = -(size / 2);
	}
	return (pt);
}

void	draw_point(t_env *e)
{
	/*
	int	i;
	int	j;

	i = 100;
	while (i < 120)
	{
		j = 100;
		while (j < 120)
		{
//			px_to_img(e, i, j);
			j++;
		}
		i++;
	}
	*/
//	static	int	i = 0;
	int			size = 50;
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*pt3;
	t_matrix	*pt4;
	t_matrix	*pt5;
	t_matrix	*mat_line;
	t_matrix	*color;
	t_matrix	*color2;
	static	int	rot = 0;
//	t_matrix	*rot;
	/*
	static	double		ang_x = 0;
	static	double		ang_y = 0;
	static	double		ang_z = 0;
	*/
	
	if (!(pt1 = matrix_init(4, 1))
		|| !(color = matrix_init(3, 1))
		|| !(color2 = matrix_init(3, 1))
		|| !(pt4 = matrix_init(4, 1))
		|| !(pt5 = matrix_init(4, 1)))
		return ;

	color->m[R] = e->r;
	color->m[G] = e->g;
	color->m[B] = e->b;

	color2->m[R] = 0;
	color2->m[G] = 0;
	color2->m[B] = 0;


	pt1->m[X] = 300;
	pt1->m[Y] = 300;
	pt1->m[Z] = 255;
	
	pt2 = sqr_rotate(rot, size);
	pt3 = matrix_add(pt1, pt2); 
	pt3->m[Z] = 0;

	mat_line = init_mat_line(pt1, pt2, color, color2);
	draw_line2(e, mat_line);
//	draw_line(e, pt3, pt1);

	pt4->m[X] = 300;
	pt4->m[Y] = 500;
	pt4->m[Z] = 255;

	pt5->m[X] = 300;
	pt5->m[Y] = 600;
	pt5->m[Z] = 0;
//	draw_line(e, pt4, pt5);

	pt4->m[X] = 350;
	pt4->m[Y] = 500;

	pt5->m[X] = 400;
	pt5->m[Y] = 700;
//	draw_line(e, pt5, pt4);

	rot += 1;

	
//	usleep(250000);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

	free(pt1);
	free(pt2);
	free(pt3);
	free(pt4);
	free(pt5);
//	free(color);
}
