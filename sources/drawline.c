/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/06 09:19:41 by fjanoty          ###   ########.fr       */
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
	
	z = (z < 0) ? 0: z;
	z = (z > 255) ? 255: z;
	color = 255 << 16 | (int)z << 8 | (int)z;
	return (color);
}

void	draw_vertical_line(t_env *e, t_matrix *pos, int beg_z, double delta_z)
{
	int	i;

	i = 0;
	if (!(pos->m[Y2] - pos->m[Y1]))
		pos->m[Y2]++;
	if (pos->m[Y2] > pos->m[Y1])
	{
//		while (pos->m[Y1] <= pos->m[Y2] && pos->m[Y1] <= pos->m[MAX_Y])
		while (pos->m[Y1] <= pos->m[Y2])
		{
			px_to_img(e, pos->m[X], pos->m[Y1], beg_z + set_color(i * delta_z));
			pos->m[Y1]++;
			i++;
		}
	}
	else
	{
//		while (pos->m[Y1] >= pos->m[Y2] && pos->m[Y1] >= pos->m[MAX_Y])
		while (pos->m[Y1] >= pos->m[Y2])
		{
			px_to_img(e, pos->m[X], pos->m[Y1], beg_z + set_color(i * delta_z));
			pos->m[Y1]--;
			i++;
		}
	}
}

int		draw_limit(t_env *e, t_matrix *pt1, t_matrix *pt2)
{
	t_matrix	*pt;
	double		delta_z;

	if (!(pt = matrix_init(3, 1)))
		return (0);
	pt->m[X] = pt1->m[X];
	pt->m[Y1] = pt1->m[Y];
	pt->m[Y2] = pt2->m[Y];
	delta_z = (pt2->m[Z] - pt1->m[Z]) / (pt2->m[Y] - pt1->m[Y]);
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
		color->m[DELTA_Z] = (pt2->m[Y] - pt1->m[Y]) / (pt2->m[X] - pt1->m[X]);
	}
	else
	{
		var->m[BEG_X] = pt2->m[X];
		var->m[END_X] = pt1->m[X];
		var->m[DELTA_Y] = (pt1->m[Y] - pt2->m[Y]) / (pt1->m[X] - pt2->m[X]);
		var->m[BEG_Y] = pt2->m[Y]; 
		color->m[BEG_Z] = pt2->m[Z];
		color->m[DELTA_Z] = (pt1->m[Y] - pt2->m[Y]) / (pt1->m[X] - pt2->m[X]);
	}
}

void	draw_line(t_env *e, t_matrix *pt1, t_matrix *pt2)
{
	int			i;
	t_matrix	*v;
	t_matrix	*pt;
	t_matrix	*c;
	int			ok;

	if ((!(pt1->m[X] - pt2->m[X]) && draw_limit(e, pt1, pt2))
		|| !(pt = matrix_init(5, 1))
		|| (!(v = matrix_init(4, 1)) && free_matrix(pt))
		|| (!(c = matrix_init(2, 1)) && free_matrix(pt) && free_matrix(v)))
		return ;
	pt->m[MAX_Y] = pt2->m[Y];
	i = -1;
	ok = 1;
	define_var(v, c, pt1, pt2);
	if (pt2->m[X] > pt1->m[X])
		while (v->m[BEG_X] + ++i <= v->m[END_X])
		{
			px_to_img(e, pt2->m[X], pt2->m[Y], 0);
			pt->m[X] = i + v->m[BEG_X];
			pt->m[Y1] = v->m[BEG_Y] + i * v->m[DELTA_Y]; 
			pt->m[Y2] = v->m[BEG_Y] + (i + 1) * v->m[DELTA_Y]; 
			draw_vertical_line(e, pt, c->m[BEG_Z], c->m[DELTA_Z] / (v->m[DELTA_Y]));
			c->m[BEG_Z] += c->m[DELTA_Z];
		}
	else if (pt2->m[X] < pt1->m[X])
		while (v->m[BEG_X] + --i >= v->m[END_X])
		{
			px_to_img(e, pt2->m[X], pt2->m[Y], 0);
			pt->m[X] = i + v->m[BEG_X];
			pt->m[Y1] = v->m[BEG_Y] + i * v->m[DELTA_Y]; 
			pt->m[Y2] = v->m[BEG_Y] + (i + 1) * v->m[DELTA_Y]; 
			draw_vertical_line(e, pt, c->m[BEG_Z], c->m[DELTA_Z] / (v->m[DELTA_Y]));
			c->m[BEG_Z] += c->m[DELTA_Z];
		}
	free_matrix(pt);
	free_matrix(c);
	free_matrix(v);
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

	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*pt3;
	t_matrix	*color;
	static	int	rot;
//	t_matrix	*rot;
	/*
	static	double		ang_x = 0;
	static	double		ang_y = 0;
	static	double		ang_z = 0;
	*/
	
	if (!(pt1 = matrix_init(4, 1))
		|| !(color = matrix_init(3, 1)))
		return ;

	color->m[R] = e->r;
	color->m[G] = e->g;
	color->m[B] = e->b;
	free_matrix(color);

	pt1->m[X] = 300;
	pt1->m[Y] = 300;
	pt1->m[Z] = 255;
	
	pt2 = sqr_rotate(rot, 50);
	pt3 = matrix_add(pt1, pt2); 

	pt3->m[Z] = 200;

	draw_line(e, pt1, pt3);
	rot += 1;

//	usleep(250000);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

	free(pt1);
	free(pt2);
	free(pt3);
//	free(color);
}
