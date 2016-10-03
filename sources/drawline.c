/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/30 20:16:34 by fjanoty          ###   ########.fr       */
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
		|| (!(org = matrix_init(6, 1))))
		return ;
	i = -1;
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	while (++i < size)
	{
		if (!(print = matrix_add(org, diff)))
		{
			dprintf(1, "###########################################################\n");
			return ;
		}
		vectpx_to_img(e, print);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&org);
}

t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2
			, t_matrix *c1, t_matrix *c2)
{
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;


	mat_line = NULL;
	diff = NULL;
	if (!(mat_line = matrix_init(14, 1))
		|| !pt1 || !pt2 || !c1 || !c2
		|| ((!(diff = matrix_sub(pt2, pt1)) && matrix_free(&mat_line))))
		return (NULL);
	diff->m[Z] = 0;
	norme = MAX(ABS(diff->m[0]), ABS(diff->m[1]));
	mat_line->m[NORME] = norme;
	matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c1->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_scalar_product(diff = matrix_sub(c2, c1), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	return (mat_line);
}

t_matrix	*init_mat_line2(t_matrix *pt_color, t_matrix *pt3, t_matrix *c3)
{
	t_matrix	*pt_inter;
	t_matrix	*color_inter;
	t_matrix	*mat_line;
	t_matrix	*diff;
	double		norme;

	if (!(pt_color) || !(pt3) || !(c3) || !(mat_line = matrix_init(14, 1))
		|| !pt_color || !pt3 || !c3
		|| !(pt_inter = matrix_init(1, 3))
		|| !(color_inter = matrix_init(1, 3)))
		return (NULL);
	ft_memmove(pt_inter->m, pt_color->m, sizeof(double) * 3);
	if (!(diff = matrix_sub(pt_inter, pt3)) && matrix_free(&mat_line))
		return (NULL);
	diff->m[Z] = 0;
	norme = matrix_dot_product(diff, diff);
	norme = sqrt(norme);
	mat_line->m[NORME] = norme;
	diff = matrix_scalar_product(diff, 1 / norme);
	ft_memmove(mat_line->m, pt3->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 3, c3->m, sizeof(double) * 3);
	ft_memmove(mat_line->m + 6, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	ft_memmove(color_inter->m, pt_color->m + 3, sizeof(double) * 3);
	matrix_scalar_product(diff = matrix_sub(color_inter, c3), 1 / norme);
	ft_memmove(mat_line->m + 9, diff->m, sizeof(double) * 3);
	matrix_free(&diff);
	matrix_free(&color_inter);
	matrix_free(&pt_inter);
	return (mat_line);
}


int		draw_triangle(t_env *e, t_matrix *mat_line, t_matrix *pt3, t_matrix *c3)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;
	t_matrix	*mat_line2;
 
	print = NULL;
	if ((!(mat_line))
		|| (!(diff = matrix_init(6, 1)))
		|| (((!(org = matrix_init(6, 1)) && matrix_free(&diff)))))
	{
		ft_putstr("y a embrouille\n");
		return (0);
	}
	ft_memmove(org->m, mat_line->m, sizeof(double) * 6);
	ft_memmove(diff->m, mat_line->m + 6, sizeof(double) * 6);
	size = (int)(mat_line->m[NORME] + 0.5);
	i = -1;
	while (++i < size)
	{
		print = matrix_add(org, diff); 
		if (!(mat_line2 = init_mat_line2(print, pt3, c3)))
		{
			ft_putstr("Yapa\n");
		}
		draw_line(e, mat_line2);
		matrix_free(&mat_line2);
		matrix_free(&org);
		org = print;
	}
	matrix_free(&diff);
	matrix_free(&print);
	return (1);
}

t_matrix	**init_color_base()
{
	static	t_matrix	**color_base = NULL;
	int					i;

	if (!color_base)
	{
		if (!(color_base = (t_matrix**)malloc(sizeof(color_base) * 3)))
			return (NULL);
		i = -1;
		while (++i < 3)
			if (!(color_base[i] = vect_new_vertfd(255 * (i == 0), 255 * (i == 1), 255 * (i == 2))))
				return (NULL);
	}
	return (color_base);
}

void	draw_base_cam(t_env *e)
{
	int			i;
	int			coef_base;
	t_matrix	*mat_line;
	t_matrix	**color_base;
	t_matrix	*pt1;
	t_matrix	*pt2;

	if (!(color_base = init_color_base())
		|| !(pt1 = matrix_init(1, 3))
		|| !(pt2 = matrix_init(1, 3)))
		return ;
	coef_base = 50;
	pt1->m[0] = -(e->ecr_x * 0.5) + 2 * coef_base;
	pt1->m[1] = -(e->ecr_y * 0.5) + 2 * coef_base;
	i = 0;
	while (i < 3)
	{
		pt2->m[0] = e->cam->base[i]->m[0] * coef_base + pt1->m[0];
		pt2->m[1] = e->cam->base[i]->m[1] * coef_base + pt1->m[1];
		if (!(mat_line = init_mat_line(pt1, pt2, color_base[i], color_base[i])))
			return ;
		draw_line(e, mat_line);
		matrix_free(&mat_line);
		i++;
	}
	matrix_free(&pt1);
	matrix_free(&pt2);
}

void	write_map(t_env *e, t_matrix	***map)
{
	int	i;
	int	j;
	
	(void)map;
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_y)
		{
			dprintf(1, "	%f", map[j][i]->m[2]);
			i++;
		}
		dprintf(1, "	<----\n");
		j++;
	}
}

void	conique_adapte(t_matrix *vect)
{
	double	norme;

	norme = vect->m[2] / 500;
	vect->m[0] /= norme;
	vect->m[1] /= norme;
}

int		is_out(t_matrix *vect, t_env *e)
{
	if (vect->m[0] < e->ecr_x * -0.5
		|| vect->m[0] > e->ecr_x * 0.5
		|| vect->m[1] < e->ecr_y * -0.5
		|| vect->m[1] > e->ecr_y * 0.5)
		return (1);
	return (0);
}


int		are_they_out(t_matrix *vect1, t_matrix *vect2, t_env *e)
{
	if (!vect1 || !vect2 || !e 
		|| ((is_out(vect1, e) && is_out(vect2, e))
		|| vect1->m[2] < 1 || vect2->m[2] < 1))
		return (1);
	return (0);
}


void	draw_face_map(t_env *e, t_matrix ***map)
{
	int			j;
	int			i;
	t_matrix	*mat_line;
	t_matrix	*c1;
	t_matrix	*c2;

	j = 0;
	mat_line = NULL;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			c1 = e->color_map[j][i];
			if (i > e->size_map_x - 2 || j > e->size_map_y - 2
				|| (!(c1 = e->color_map[j][i]))
				|| (!(c2 = e->color_map[j + 1][i + 1]))
				|| (!(mat_line = init_mat_line(map[j][i], map[j + 1][i + 1], c1, c2)))
				|| (!(c2 = e->color_map[j][i + 1]))
				|| (!draw_triangle(e, mat_line, map[j][i + 1], c2))
				|| (!(c2 = e->color_map[j + 1][i]))
				|| !dprintf(1, "--aa") || ((!draw_triangle(e, mat_line, map[j + 1][i], c2))) || !dprintf(1, "aa--	\n"))
				matrix_free(&mat_line);
			else
				matrix_free(&mat_line);
			i++;
		}
		j++;
	}
}

t_matrix	*base_change_scalar(t_cam *cam, t_matrix *vect)
{
	t_matrix	*tmp;

	if (!(tmp = matrix_init(1, 3)))
		return (NULL);
	tmp->m[0] = matrix_dot_product(cam->base[0], vect);
	tmp->m[1] = matrix_dot_product(cam->base[1], vect);
	tmp->m[2] = matrix_dot_product(cam->base[2], vect);
	return (tmp);
}

void	base_change(t_env *e, t_cam *cam, t_matrix	***map)
{
	int	i;
	int	j;
	t_matrix	*tmp;
	t_matrix	*rot_obj;
	t_matrix	*rot_cam;
	
	j = 0;
	rot_cam = NULL;	
	if (!(rot_obj = set_rotate(e->rot_x, e->rot_y, e->rot_z))
		|| !(rot_cam = set_rotate(cam->rot->m[0], cam->rot->m[1], cam->rot->m[2])))
		return ;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			tmp = matrix_product(rot_obj, map[j][i]);
			matrix_free(map[j] + i);
			matrix_sub_in(tmp, cam->pos, tmp);
			map[j][i] = base_change_scalar(cam, tmp);
			matrix_free(&tmp);
			conique_adapte(map[j][i]);
			i++;
		}
		j++;
	}
	matrix_free(&rot_obj);
	matrix_free(&rot_cam);
}


void	draw_link_map(t_env *e, t_matrix ***map)
{
	int			j;
	int			i;
	t_matrix	*mat_line;
	t_matrix	*colore;
	t_matrix	*colore2;

	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)	
		{
			colore = e->color_map[j][i];
//*
			if (i > (e->size_map_x - 2) || !(colore2 = e->color_map[j][i + 1])
				|| !(mat_line = init_mat_line(map[j][i], map[j][i + 1], colore, colore2))
				|| (are_they_out(map[j][i], map[j][i + 1], e) && matrix_free(&mat_line)))
				;
			else
			{
				draw_line(e, mat_line);
				matrix_free(&mat_line);
			}	
//*/
/*
			if (j > (e->size_map_y - 2) || !(colore2 = e->color_map[j + 1][i])
				|| !(mat_line = init_mat_line(map[j][i], map[j + 1][i], colore, colore2))
				|| (are_they_out(map[j][i], map[j + 1][i], e) && matrix_free(&mat_line)))
				;
			else
			{
				draw_line(e, mat_line);
				matrix_free(&mat_line);
			}	
*/
			i++;
		}
		j++;
	}
}

void	draw_link_map2(t_env *e, t_matrix ***map)
{
	int			j;
	int			i;
	t_matrix	*mat_line;
	t_matrix	*colore;
	t_matrix	*colore2;

	j = 0;
	colore = vect_new_vertfd(0, 0, 0);
	colore2 = vect_new_vertfd(0, 0, 0);
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)	
		{
			if (i > (e->size_map_x - 2)
				|| !(mat_line = init_mat_line(map[j][i], map[j][i + 1], colore, colore2))
				|| (are_they_out(map[j][i], map[j][i + 1], e) && matrix_free(&mat_line)))
				;
			else
			{
				draw_line(e, mat_line);
				matrix_free(&mat_line);
			}	
			if (j > (e->size_map_y - 2)
				|| !(mat_line = init_mat_line(map[j][i], map[j + 1][i], colore, colore2))
				|| (are_they_out(map[j][i], map[j + 1][i], e) && matrix_free(&mat_line)))
				;
			else
			{
				draw_line(e, mat_line);
				matrix_free(&mat_line);
			}	
			i++;
		}
		j++;
	}
	matrix_free(&colore);
	matrix_free(&colore2);
}

t_matrix***	copy_vect_map(t_env *e)
{
	int	i;
	int	j;
	t_matrix	***map;

	if (!(map = (t_matrix***)malloc(sizeof(t_matrix**) * e->size_map_y)))
		return (NULL);
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		if (!(map[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->size_map_x)))
			return (NULL);
		while (i < e->size_map_x)
		{
			map[j][i] = matrix_copy(e->vect_map[j][i]);
			i++;
		}
		j++;
	}
	return (map);
}

t_matrix	*finishe_color_actu(t_env *e, double *pak, double pos, double max)
{
	t_matrix	*color;

	if (e->color_max != 0 && e->color_min < 0)
		pak[0] = 255 * pak[3] / e->color_max;
	else if (pak[2] != 0)
		pak[0] = 255 * pak[3] / pak[2];
	else
		pak[0] = 255;
	pak[1] = 255 - pak[0];
	if (!(color = vect_new_vertfd(pak[0] * pos / max, pak[1] * pos / max, 0)))
		return (NULL);
	return (color);
}
t_matrix	*set_color_actu(t_env *e, double value, double pos, double max)
{
	t_matrix	*color;
	double		pak[4];

	pak[3] = value;
	pak[2] = e->color_max - e->color_min;
	color = NULL;
	pak[0] = 0;
	if (pak[3] < 0)
	{
		if (e->z_max > 0)
			pak[0] = 255 * pak[3] / e->color_min;
		else if (pak[2] > 0)
			pak[0] = 255 * pak[3] / pak[2];
		else
			pak[0] = 255;
		pak[1] = 255 - pak[0];
		if (!(color = vect_new_vertfd(0, pak[1] * pos / max, pak[0] * pos / max)))
			return (NULL);
	}
	else
		color = finishe_color_actu(e, pak, pos, max);
	return (color);
}

void	actu_emp_color(t_env *e)
{
	static	double	min = 0;
	static	double	max = 0;
	int			i;
	int			j;

	e->color_min = -20;//e->vect_map[0][0]->m[2];i
	e->color_max = 20;//e->vect_map[0][0]->m[2];
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			if (e->vect_map[j][i]->m[2] > e->color_max)
				e->color_max =  e->vect_map[j][i]->m[2];
			if (e->vect_map[j][i]->m[2] < e->color_min)
				e->color_min =  e->vect_map[j][i]->m[2];
			i++;
			min = MIN(min, e->color_min);
			max = MAX(max, e->color_max);
//			dprintf(1, "min:%lf	max:%lf\n", min, max);
		}
		j++;
	}
}

int		map_color_actu(t_env *e)
{
	int			i;
	int			j;

	actu_emp_color(e);
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			matrix_free(e->color_map[j] + i);
			if (!(e->color_map[j][i] = set_color_actu(e, e->vect_map[j][i]->m[2], i, e->size_map_x)))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

void	main_work(t_env *e)
{	
	t_matrix ***map;

	if (!(map = get_map(e)))
		return ;
	e->vect_map = map;
	map_color_actu(e);
	base_change(e, e->cam, map);
	e->vect_map = map;
	if (e->draw % 2 == 0)
		draw_link_map(e, e->vect_map);
	else
	{
		draw_face_map(e, e->vect_map);
		draw_link_map2(e, e->vect_map);
	}
	draw_base_cam(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_do_sync(e->mlx);
	free_map(&map, e);
}
