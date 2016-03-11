/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/09 16:13:41 by fjanoty          ###   ########.fr       */
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
static int debug = 0;

dprintf(1, "non\n");
	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| (!(org = matrix_init(6, 1)) && matrix_free(&diff)))
		return ;
dprintf(1, "oui\n");
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
dprintf(1, "move1\n");
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
dprintf(1, "move2\n");
dprintf(1, "adr:%ld\n", (long)mat_line->m);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size - 1)
	{
dprintf(1, "move3:%d debug%d len:%d\n", i, debug, size);
		print = matrix_add(org, diff); 
		vectpx_to_img(e, print);
dprintf(1, "avant\n");
		matrix_free(&org);
dprintf(1, "apres :%ld\n", (long)(org = print));
		
	}
	debug++;
dprintf(1, "Mais la je en dis pas\n");
//	matrix_free(&org);
	matrix_free(&diff);
	matrix_free(&print);
dprintf(1, "c'est pas trop la le bug\n");
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2
			, t_matrix *c1, t_matrix *c2)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	if (pt1)
		dprintf(1, "pt1\n");
	if (pt2)
		dprintf(1, "pt2\n");
	if (c1)
		dprintf(1, "c1\n");
	if (c2)
		dprintf(1, "c2\n");
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| (!(diff = matrix_sub(pt1, pt2)) && free_matrix(mat_line)))
		return (NULL);
	dprintf(1, "ouiiiiiiiiii\n");
	diff->m[Z] = 0;
	norme = matrix_dot_product(diff, diff);
	dprintf(1, "carrer:%f\n", norme);
	norme = sqrt(norme);
	dprintf(1, "norme:%f [%d]\n", norme, NORME);
	mat_line->m[NORME] = norme;
	diff = matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	matrix_scalar_product(diff = matrix_sub(c1, c2), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	return (mat_line);
}

t_matrix	*sqr_rotate(int rot, int x, int y, int size)
{
	t_matrix	*pt;
	int			a;
	int			b;
	int			val;

	if (!(pt = matrix_init(4, 1)))
		return (NULL);
	a = rot % size == rot % (size * 2);
	b = rot % (size * 2) == rot % (size * 4);
	val = rot % size;
	pt->m[2] = 0;
	pt->m[3] = 0;
	if (a && b)
	{
		pt->m[0] = x -(size / 2);
		pt->m[1] = y + val - size / 2;
	}
	else if (!a && b)
	{
		pt->m[0] = x + val - size / 2;
		pt->m[1] = y + (size / 2);
	}
	else if (a && !b)
	{
		pt->m[0] = x + size / 2;
		pt->m[1] = y + size / 2 - val;
	}
	else if (!a && !b)
	{
		pt->m[0] = x + size / 2 - val;
		pt->m[1] = y -(size / 2);
	}
	return (pt);
}

void	test_new_px(t_env *e)
{
	//*
	int	i;
	int	j;
	t_matrix	*test;

	test = matrix_init(6,1);

	i = 0;
	while (i < 120)
	{
		j = 0;
		while (j < 120)
		{
			test->m[X] = 100 +i; 
			test->m[Y] = 50 +j; 
			test->m[Z] = 100; 

			test->m[3] = 100 + i; 
			test->m[4] = 100 + j; 
			test->m[5] = 150 - i + j; 

			vectpx_to_img(e, test);
			j++;
		}
		i++;
	}
//	*/
}


void	draw_pointi_new(t_env *e)
{
	test_new_px(e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

}

void	draw_point(t_env *e)
{

//	static	int	i = 0;
	int			size = 300;
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


	color2->m[R] = 255;
	color2->m[G] = 255;
	color2->m[B] = 255;

	pt1->m[X] = 300;
	pt1->m[Y] = 300;
	pt1->m[Z] = 0;



	pt2 = sqr_rotate(rot, pt1->m[X], pt1->m[Y], size);
	pt3 = matrix_add(pt1, pt2); 

	pt3->m[Z] = 0;

	dprintf(1, "c'est lui\n");
	if (!(mat_line = init_mat_line(pt1, pt2, color2, color)))
			dprintf(1, "All is well\n");
	dprintf(1, "c'est moi\n");
	matrix_print(mat_line);
//	int k = 0;
//	while (k < 12)
//	{
//		dprintf(1, "[%d]=%f\n", k, mat_line->m[k]);
//		k++;
//	}
dprintf(1, "seg befor it was cool\n");
	draw_line2(e, mat_line);

	pt4 = matrix_copy(pt1);
	pt5 = matrix_copy(pt2);
	pt4->m[Y] -= 1; 
	pt5->m[Y] -= 1; 

	matrix_free(&mat_line);
	if (!(mat_line = init_mat_line(pt4, pt5, color2, color)))
			dprintf(1, "All is well\n");
	draw_line2(e, mat_line);


dprintf(1, "this will never hpened\n");
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

	
	usleep(250000);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

	free(pt1);
	free(pt2);
	free(pt3);
	free(pt4);
	free(pt5);
	free(color);
	free(color2);
}


/*
 void	px_to_img(t_env *e, int x, int y, int color)
{
//	(void)color;
//	printf("color:%0x\n", color);
//	printf("	r:%0x\n", (color & 0x00FF0000) >> 16);
//	printf("	v:%0x\n", (color & 0x0000FF00) >> 8);
//	printf("	b:%0x\n", (color & 0x000000FF) );
	y = 100;
	e->data[y * e->size_line + x * 4 + 2] = (color & 0x00FF0000) >> 16;
	e->data[y * e->size_line + x * 4 + 1] = (color & 0x0000FF00) >> 8;
	e->data[y * e->size_line + x * 4] = (color & 0x000000FF);
	dprintf(1, "x:%d y:%d  color:%d\n", x, y, color);
}

void	vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int) pos_color->m[0];
	y = (int) pos_color->m[1];
	r = (int) pos_color->m[3];
	g = (int) pos_color->m[4];
	b = (int) pos_color->m[5];
	y = 100;
	e->data[y * e->size_line + x * 4 + 2] = 255;
	e->data[y * e->size_line + x * 4 + 1] = 255;
	e->data[y * e->size_line + x * 4] = 255;
	dprintf(1, "x:%d y:%d  r:%d v:%d b:%d\n", x, y, r, g, b);
}

 * */