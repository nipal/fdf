/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/05 15:47:49 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>

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

void	draw_vertical_line(t_env *e, t_matrix *pos, t_matrix *color)
{
	int	x;
	int	y1;
	int	y2;

	x = pos->m[0];
	y1 = pos->m[1];
	y2 = pos->m[2];
	if (!(y2 - y1))
		y2++;
	while (y1 < y2)
	{
		px_to_img(e, x, y1, color);
		y1++;
	}
}

//	x	-> m->[0]
//	y1	-> m->[1]
//	y2	-> m->[2]

int		draw_limit(t_env *e, t_matrix *pt1, t_matrix *pt2, t_matrix *color)
{
	t_matrix	*pt;

	if (!(pt = matrix_init(3, 1)))
		return (1);
	pt->m[0] = pt1->m[X];
	pt->m[1] = MIN(pt1->m[Y], pt2->m[Y]);
	pt->m[2] = MAX(pt1->m[Y], pt2->m[Y]);
	draw_vertical_line(e, pt, color);
	free_matrix(pt);
	return (1);
}

void	draw_line(t_env *e, t_matrix *pt1, t_matrix *pt2, t_matrix *color)
{
	int		i;
	int		begin_x;
	int		end_x;
	double	delta_y;
	t_matrix	*pt;

	if (!(pt = matrix_init(4, 1)))
		return ;
	if (!(pt1->m[X] - pt2->m[X]) && draw_limit(e, pt1, pt2, color))
		return ;
	i = -1;
	begin_x = (pt1->m[X] <= pt2->m[X]) ? pt1->m[X] : pt2->m[X];
	pt->m[3] = (pt1->m[X] <= pt2->m[X]) ? pt1->m[Y] : pt2->m[Y];
	end_x = (pt1->m[X] > pt2->m[X]) ? pt1->m[X] : pt2->m[X];
	delta_y = pt2->m[Y] - pt1->m[Y];
	delta_y = (pt1->m[X] <= pt2->m[X]) ? delta_y : -delta_y;
	delta_y /= ABS(pt2->m[X] - pt1->m[X]);
	while (begin_x + ++i < end_x)
	{
		pt->m[0] = (i) + begin_x;
		pt->m[1] = pt->m[3] + MIN(i * delta_y, (i + 1) * delta_y); 
		pt->m[2] = pt->m[3] + MAX(i * delta_y, (i + 1) * delta_y); 
		draw_vertical_line(e, pt, color);
	}
	free_matrix(pt);
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

	pt1->m[X] = 300;
	pt1->m[Y] = 300;
	pt1->m[2] = 0;
	pt1->m[2] = 0;
	pt1->m[3] = 0;
	

	pt2 = sqr_rotate(rot, 400);
	pt3 = matrix_add(pt1, pt2); 
	draw_line(e, pt1, pt3, color);
	rot += 11;

//	usleep(250000);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

	free(pt1);
	free(pt2);
	free(pt3);
	free(color);
}
