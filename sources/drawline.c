/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/24 11:32:24 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include "c_maths.h"
#include <unistd.h>
#include <stdio.h>

void	print_triangle(t_env *e, t_matrix **pt, t_matrix **cl);

void	draw_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

(void)e;
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
//	;//dprintf(1, "SIR! \n");
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;


	mat_line = NULL;
	diff = NULL;
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| (!(diff = matrix_sub(pt2, pt1)) && free_matrix(mat_line)))
	{
//		if (!(mat_line))
//			;//dprintf(1, "no mat_line\n");
//		if (!(pt1))
//			;//dprintf(1, "no pt1\n");
//		if (!(pt2))
//			;//dprintf(1, "no pt2\n");
//		if (!(c1))
//			;//dprintf(1, "no c1\n");
//		if (!(c2))
//			;//dprintf(1, "no c2\n");
//		if (!(diff))
//			;//dprintf(1, "no diff\n");
//		return (NULL);
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
//	;//dprintf(1, "Yes SIR!\n");
	return (mat_line);
}

t_matrix	*init_mat_line2(t_matrix *pt_color, t_matrix *pt3, t_matrix *c3)
{
	t_matrix	*pt_inter;
	t_matrix	*color_inter;
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

//	if (!(pt_color))
//		;//dprintf(1, "	pt_color\n");
//	if (!(pt3))
//		;//dprintf(1, "	pt3\n");
//	if (!(c3))
//		;//dprintf(1, "	c3\n");
	if (!(mat_line = matrix_init(14, 1))
		|| !pt_color || !pt3 || !c3
		|| !(pt_inter = matrix_init(1, 4))
		|| !(color_inter = matrix_init(1, 4)))
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
	(void)mat_line2;
	(void)pt3;
	(void)c3;
	(void)e;

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
//		if (!(mat_line2 = init_mat_line2(print, pt3, c3)))
//		{
//			;//dprintf(1, "Yapa\n");
//		}
//		draw_line(e, mat_line2);
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

	if (!(pt = matrix_init(1, 4)))
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
	t_matrix	*min;	
	t_matrix	*pos;	
	t_matrix	*color;	

	min = matrix_put_in_new(-100, -100, 0, 0);
	pos = matrix_put_in_new(100, 100, 0, 0);
	color = matrix_put_in_new(255, 255, 255, 0);

	print_repaire(min, pos, color, e);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);
}






void	draw_point_new(t_env *e)
{
	double	z_max;
	double	z_min;
//(void)e;

	t_matrix ***map = get_map(e, &z_max, &z_min);
	(void)map;
//	;//dprintf(1, "map:%ld\n", (long)map);
//	;//dprintf(1, "*map:%ld\n", (long)*map );
//	;//dprintf(1, "**map:%ld\n", (long)**map);
//map;
//	t_cam	*cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 *M_PI, e);

	print_map(e, e->cam, map);
//	(void)cam;
//	(void)e;

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);
}

void	draw_point_test(t_env *e)
{
	t_matrix	*pt1;
	t_matrix	*pt2;
	t_matrix	*pt3;
	t_matrix	*c1;
	t_matrix	*c2;
	t_matrix	*c3;
	t_matrix	**pt;
	t_matrix	**cl;
//	t_matrix	**tab;
	int			size = 500;
	static	int	rot = 0;

	pt1 = matrix_put_in_new(500, 500, 100, 1);
	pt2 = sqr_rotate(rot, pt1->m[X], pt1->m[Y], size);
	pt3 = sqr_rotate(rot++ + size, pt1->m[X], pt1->m[Y], size);
	c1 = matrix_put_in_new(130, 0, 170, 1);
	c2 = matrix_put_in_new(0, 0, 0, 1);
	c3 = matrix_put_in_new(0, 0, 0, 1);

	pt = tab_matrix(pt1, pt2, pt3);
//	dprintf(1, "oui\n");
//	dprintf(1, "c1:%ld\n", (long)c1);
//	dprintf(1, "c2:%ld\n", (long)c2);
//	dprintf(1, "c3:%ld\n", (long)c3);
	cl = tab_matrix(c1, c2, c3);
	print_triangle(0, pt, cl);
//	print_triangle(0, tab_matrix(pt2, pt1, pt3), 0);
//	print_triangle(0, tab_matrix(pt1, pt3, pt2), 0);

	print_line(pt1, c1, pt2, c2);
	print_line(pt2, c2, pt3, c3);
	print_line(pt3, c3, pt1, c1);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	print_state(e);
	mlx_do_sync(e->mlx);
	matrix_free(&pt1);
	matrix_free(&pt2);
	matrix_free(&pt3);
	matrix_free(&c1);
	matrix_free(&c2);
	matrix_free(&c3);
//	usleep(100000);
}
