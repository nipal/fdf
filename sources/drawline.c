/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/16 00:54:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	draw_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| (!(org = matrix_init(6, 1)) && matrix_free(&diff)))
		return ;
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size)
	{
		print = matrix_add(org, diff); 
		vectpx_to_img(e, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&print);
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2
			, t_matrix *c1, t_matrix *c2)
{
//	dprintf(1, "SIR! \n");
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;


	mat_line = NULL;
	diff = NULL;
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| (!(diff = matrix_sub(pt2, pt1)) && free_matrix(mat_line)))
	{
		if (!(mat_line))
			dprintf(1, "no mat_line\n");
		if (!(pt1))
			dprintf(1, "no pt1\n");
		if (!(pt2))
			dprintf(1, "no pt2\n");
		if (!(c1))
			dprintf(1, "no c1\n");
		if (!(c2))
			dprintf(1, "no c2\n");
		if (!(diff))
			dprintf(1, "no diff\n");
		return (NULL);
	}
	diff->m[Z] = 0;
	norme = matrix_dot_product(diff, diff);
	norme = sqrt(norme);
	mat_line->m[NORME] = norme;
	diff = matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	matrix_scalar_product(diff = matrix_sub(c2, c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	free_matrix(diff);
//	dprintf(1, "Yes SIR!\n");
	return (mat_line);
}

t_matrix	*init_mat_line2(t_matrix *pt_color, t_matrix *pt3, t_matrix *c3)
{
	t_matrix	*pt_inter;
	t_matrix	*color_inter;
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	if (!(pt_color))
		dprintf(1, "	pt_color\n");
	if (!(pt3))
		dprintf(1, "	pt3\n");
	if (!(c3))
		dprintf(1, "	c3\n");
	if (!(mat_line = matrix_init(14, 1))
		|| !pt_color || !pt3 || !c3
		|| !(pt_inter = matrix_init(4, 1))
		|| !(color_inter = matrix_init(4, 1)))
		return (NULL);
	ft_memmove(pt_inter->m, pt_color->m, sizeof(double) * 3);
	if (!(diff = matrix_sub(pt_inter, pt3)) && free_matrix(mat_line))
		return (NULL);
	diff->m[Z] = 0;
	norme = matrix_dot_product(diff, diff);
	norme = sqrt(norme);
	mat_line->m[NORME] = norme;
	diff = matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt3->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c3->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	ft_memmove(color_inter->m, pt_color->m + 3, sizeof(double) * 3);
	matrix_scalar_product(diff = matrix_sub(color_inter, c3), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	free_matrix(diff);
	return (mat_line);
}


void	draw_triangle(t_env *e, t_matrix *mat_line, t_matrix *pt3, t_matrix *c3)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;
	t_matrix	*mat_line2;

	if (!(mat_line)
		|| !(diff = matrix_init(6, 1))
		|| (!(org = matrix_init(6, 1)) && matrix_free(&diff)))
		return ;
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size)
	{
		print = matrix_add(org, diff); 
		if (!(mat_line2 = init_mat_line2(print, pt3, c3)))
		{
			dprintf(1, "Yapa\n");
		}
		draw_line(e, mat_line2);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&print);
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



void	draw_point(t_env *e)
{
	// On veux juste tracer la map
	double	z_max;
	double	z_min;
//(void)e;

	t_matrix ***map = get_map(&z_max, &z_min);
	(void)map;
//	dprintf(1, "map:%ld\n", (long)map);
//	dprintf(1, "*map:%ld\n", (long)*map );
//	dprintf(1, "**map:%ld\n", (long)**map);
//map;
//	t_cam	*cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 *M_PI, e);

	print_map(e, e->cam, map);
//	(void)cam;
//	(void)e;

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);
}

void	draw_point_old(t_env *e)
{

	int			size = 199;
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*pt3;
	t_matrix	*pt4;
	t_matrix	*pt5;
	t_matrix	*mat_line;
	t_matrix	*color;
	t_matrix	*color2;
	t_matrix	*color3;
	t_matrix	*rotate;
//	t_matrix	*rotat2;

	static	double		angle;
	static	int	rot = 0;



	
//dprintf(1, "\n\nAll is well 2\n");
	
	if (!(pt1 = matrix_init(4, 1))
		|| !(color = matrix_init(4, 1))
		|| !(color2 = matrix_init(4, 1))
		|| !(color3 = matrix_init(4, 1))
		|| !(pt2 = matrix_init(4, 1))
		|| !(pt4 = matrix_init(4, 1))
		|| !(pt5 = matrix_init(4, 1))
//		|| !(rotate2 = set_rotate(M_PI * (angle / 360), 0, 0))
		|| !(rotate = set_rotate(M_PI * (angle / 360), 0, 0)))
		return ;
//	dprintf(1, "ang:%f", angle);


	matrix_buffer(color);
	matrix_put_in(0, 0, e->b, 1);
	matrix_buffer(color2);
	matrix_put_in(e->r, 0, 0, 1);
	matrix_buffer(color3);
	matrix_put_in(0, e->g, 0, 1);
	/*
	color2->m[R] = 255;
	color2->m[G] = 255;
	color2->m[B] = 255;
	color2->m[3] = 1;
//	*/

	pt1->m[X] = 300;
	pt1->m[Y] = 300;
	pt1->m[Z] = 0;

//	pt2->m[X] = 100;
//	pt2->m[Y] = 0;
//	pt2->m[Z] = 0;
//	pt2->m[3] = 0;

	matrix_buffer(pt2);
	matrix_put_in(100, 0, 0, 0);

	pt3 = matrix_product(pt2, rotate);
	pt5 = matrix_add(pt1, pt3); 
//	pt4 = matrix_product(pt1, rotate);
	pt4 = sqr_rotate(rot, pt1->m[X], pt1->m[Y], size);
	/*
	pt4 = matrix_add(pt1, pt3); 
	pt4 = matrix_add(pt1, pt3); 
	pt4 = matrix_add(pt1, pt3); 
	pt4 = matrix_add(pt1, pt3); 
	pt4 = matrix_add(pt1, pt3); 
	pt4 = matrix_add(pt3, pt1); 
//*/

	if (!(rotate))
		ft_putstr("not rotate\n");
	if (!(pt1))
		ft_putstr("not pt1\n");
	if (!(pt2))
		ft_putstr("not pt2\n");
	if (!(pt3))
		ft_putstr("not pt3\n");
	if (!(pt4))
		ft_putstr("not pt4\n");


//		dprintf(1, "\n\nAll is well 2\n");

//	ft_putstr("\n\n	le caca c'est trop delicieux\n");

/*	
	if (!(mat_line = init_mat_line(pt4, pt5, color3, color2)))
 		dprintf(1, "All is well 1\n");
	draw_triangle(e, mat_line, pt1, color);
	if (!(mat_line = init_mat_line(pt4, pt1, color3, color)))
 		dprintf(1, "All is well 1\n");
	draw_triangle(e, mat_line, pt5, color2);
//*/

//*

	if (!(mat_line = init_mat_line(pt4, pt5, color2, color3)))
		dprintf(1, "\n\nAll is well 2\n");
	draw_line(e, mat_line);


	matrix_free(&mat_line);
	if (!(mat_line = init_mat_line(pt4, pt1, color2, color)))
		dprintf(1, "All is well 3\n");
	draw_line(e, (mat_line));
	//draw_line(e, mat_line);

	matrix_free(&mat_line);
	if (!(mat_line = init_mat_line(pt1, pt5, color, color3)))
		dprintf(1, "All is well 3\n");
	draw_line(e, (mat_line));
	draw_line(e, mat_line);
//*/


	



//	write(1, "\n\n", 2);
//	matrix_display(mat_line);
//	write(1, "\n\n", 2);
/*
	matrix_display(pt1);
	write(1, "\n", 1);
	matrix_display(pt2);
	write(1, "\n\n", 2);
*/

	rot += 4 * size - 2;
	angle += 1 ;

	
//	usleep(250000);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);

	matrix_free(&pt1);
	matrix_free(&pt2);
	matrix_free(&pt3);
	matrix_free(&pt4);
	matrix_free(&pt5);
	matrix_free(&rotate);
	matrix_free(&color);
	matrix_free(&color2);
	matrix_free(&color3);
	matrix_free(&mat_line);
}
