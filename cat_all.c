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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:59:11 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/05 07:28:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"
#include "fdf.h"

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 14:35:01 by jpirsch           #+#    #+#             */
/*   Updated: 2015/04/04 09:49:05 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char *s2, int ret)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return (s1 ? s1 : s2);
	if (!(str = ft_strnew(ft_strlen(s1) + ret)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	free(s1);
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int		split_tmp(t_info *f, char **line)
{
	char		*tmp;

	*line = ft_strsub(f->s, 0, f->i);
	tmp = f->s;
	f->s = ft_strdup(&f->s[f->i + 1]);
	free(tmp);
	return (1);
}

int		split_tmp2(t_info *f, char **line)
{
	char		*tmp;

	*line = ft_strdup("");
	tmp = f->s;
	f->s = ft_strdup(f->s + 1);
	free(tmp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_info	f;
	char			buff[BUFF_SIZE + 1];

	if (fd == -1)
		return (-1);
	if (!f.s)
		f.s = ft_strdup("");
	if (f.s[0] == '\n')
		return (split_tmp2(&f, line));
	else if (!(f.i = ft_strchr_len(f.s, '\n')))
	{
		while ((f.ret = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[f.ret] = '\0';
			f.s = ft_strjoin2(f.s, buff, f.ret);
			if ((f.i = ft_strchr_len(f.s, '\n')))
				return (split_tmp(&f, line));
			else if (f.s[0] == '\n')
				return (split_tmp2(&f, line));
		}
	}
	else
		return (split_tmp(&f, line));
	return (f.ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/15 04:13:55 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

void	init_t_key(t_key *key)
{
	key->echap = 0;
	key->decal_down = 0;
	key->decal_up = 0;
	key->decal_right = 0;
	key->decal_left = 0;
	key->zoom = 0;
	key->zoom_back = 0;
	key->cte1_increase = 0;
	key->cte1_decrease = 0;
	key->isometric = 0;
	key->parallel = 0;
	key->conic = 0;
	key->scale_increase = 0;
	key->scale_decrease = 0;
	key->r = 0;
	key->g = 0;
	key->b = 0;
	key->rot_z1 = 0;
	key->rot_z2 = 0;
	key->rot_x1 = 0;
	key->rot_x2 = 0;
	key->rot_y1 = 0;
	key->rot_y2 = 0;
}

int		key_press(int keycode, t_env *e)
{
	(keycode == 0) ? e->key.rot_z2 = 1 : (void)keycode;
	(keycode == 1) ? e->key.rot_x1 = 1 : (void)keycode;
	(keycode == 2) ? e->key.rot_z1 = 1 : (void)keycode;
	(keycode == 12) ? e->key.rot_y2 = 1 : (void)keycode;
	(keycode == 13) ? e->key.rot_x2 = 1 : (void)keycode;
	(keycode == 14) ? e->key.rot_y1 = 1 : (void)keycode;
	(keycode == 53) ? e->key.echap = 1 : (void)keycode;
	(keycode == 53) ? e->key.echap = 1 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 1 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 1 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 1 : (void)keycode;
	(keycode == 123) ? e->key.decal_left = 1 : (void)keycode;
	(keycode == 69) ? e->key.zoom = 1 : (void)keycode;
	(keycode == 78) ? e->key.zoom_back = 1 : (void)keycode;
	(keycode == 24) ? e->key.scale_increase = 1 : (void)keycode;
	(keycode == 27) ? e->key.scale_decrease = 1 : (void)keycode;
	(keycode == 2) ? e->key.cte1_increase = 1 : (void)keycode;
	(keycode == 0) ? e->key.cte1_decrease = 1 : (void)keycode;
	(keycode == 34) ? e->key.isometric = 1 : (void)keycode;
	(keycode == 35) ? e->key.parallel = 1 : (void)keycode;
	(keycode == 8) ? e->key.conic = 1 : (void)keycode;
	(keycode == 15) ? e->key.r = 1 : (void)keycode;
	(keycode == 5) ? e->key.g = 1 : (void)keycode;
	(keycode == 11) ? e->key.b = 1 : (void)keycode;
	return (1);
}

int		key_release(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	(keycode == 0) ? e->key.rot_z2 = 0 : (void)keycode;
	(keycode == 1) ? e->key.rot_x1 = 0 : (void)keycode;
	(keycode == 2) ? e->key.rot_z1 = 0 : (void)keycode;
	(keycode == 12) ? e->key.rot_y2 = 0 : (void)keycode;
	(keycode == 13) ? e->key.rot_x2 = 0 : (void)keycode;
	(keycode == 14) ? e->key.rot_y1 = 0 : (void)keycode;
	(keycode == 53) ? e->key.echap = 0 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 0 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 0 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 0 : (void)keycode;
	(keycode == 123) ? e->key.decal_left = 0 : (void)keycode;
	(keycode == 69) ? e->key.zoom = 0 : (void)keycode;
	(keycode == 78) ? e->key.zoom_back = 0 : (void)keycode;
	(keycode == 24) ? e->key.scale_increase = 0 : (void)keycode;
	(keycode == 27) ? e->key.scale_decrease = 0 : (void)keycode;
	(keycode == 2) ? e->key.cte1_increase = 0 : (void)keycode;
	(keycode == 0) ? e->key.cte1_decrease = 0 : (void)keycode;
	(keycode == 34) ? e->key.isometric = 0 : (void)keycode;
	(keycode == 35) ? e->key.parallel = 0 : (void)keycode;
	(keycode == 8) ? e->key.conic = 0 : (void)keycode;
	(keycode == 15) ? e->key.r = 0 : (void)keycode;
	(keycode == 5) ? e->key.g = 0 : (void)keycode;
	(keycode == 11) ? e->key.b = 0 : (void)keycode;
	return (1);
}

int		loop_hook(t_env *e)
{
	double	increm;
	
	increm = 0.03;
//	dprintf(1, "x:%f y:%f x:%f\n", e->rot_x, e->rot_y, e->rot_z);
	(e->key.rot_z2 == 1) ? e->rot_z -= increm : (void)e;
	(e->key.rot_x2 == 1) ? e->rot_x -= increm : (void)e;
	(e->key.rot_z1 == 1) ? e->rot_z += increm : (void)e;
	(e->key.rot_y2 == 1) ? e->rot_y -= increm : (void)e;
	(e->key.rot_x1 == 1) ? e->rot_x += increm : (void)e;
	(e->key.rot_y1 == 1) ? e->rot_y += increm : (void)e;
	(e->key.echap == 1) ? exit(0) : (void)e->key.echap;
	(e->key.decal_down == 1) ? e->decaly -= e->zoom / 2 : (void)e->key.echap;
	(e->key.decal_up == 1) ? e->decaly += e->zoom / 2 : (void)e->key.echap;
	(e->key.decal_right == 1) ? e->decalx -= e->zoom / 2 : (void)e->key.echap;
	(e->key.decal_left == 1) ? e->decalx += e->zoom / 2 : (void)e->key.echap;
	(e->key.zoom == 1) ? e->zoom += 4 : (void)e->key.echap;
	(e->key.zoom_back == 1) ? e->zoom -= 4 : (void)e->key.echap;
	(e->key.scale_increase == 1) ? e->scale += 0.2 : (void)e->key.echap;
	(e->key.scale_decrease == 1) ? e->scale -= 0.2 : (void)e->key.echap;
	(e->key.cte1_increase == 1) ? e->cte1 += 0.01 : (void)e->key.echap;
	(e->key.cte1_decrease == 1) ? e->cte1 -= 0.01 : (void)e->key.echap;
	(e->key.isometric == 1) ? e->proj = 0 : (void)e->key.echap;
	(e->key.parallel == 1) ? e->proj = 1 : (void)e->key.echap;
	(e->key.conic == 1) ? e->proj = 2 : (void)e->key.echap;
	(e->key.r == 1) ? e->r += 20 : (void)e->key.echap;
	(e->key.g == 1) ? e->g += 20 : (void)e->key.echap;
	(e->key.b == 1) ? e->b += 20 : (void)e->key.echap;
	ft_bzero(e->data, e->size_line * 990);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y);
	draw_point(e);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 07:31:16 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/06 09:19:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

int		check_map(int fd)
{
	char	buf[1000001];
	int		ret;

	ret = 0;
	if (fd == -1)
		return (0);
	if ((ret = read(fd, buf, 1000000)))
		buf[ret] = '\0';
	if (buf[ret - 1] != '\n')
		return (0);
	if (buf[ret - 1] == '\n' && buf[ret - 2] == '\n')
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	int		fd;
	int		**map;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = open("maps/42.fdf", O_RDONLY);
	if (fd > 0)
	{
		if (check_map(fd))
		{
			close(fd);
			if (ac == 2)
				fd = open(av[1], O_RDONLY);
			else
				fd = open("maps/42.fdf", O_RDONLY);
			if (fd > 0)
				if ((map = parse(fd)))
					env(map);
		}
		else
			ft_putendl_fd("No \\n or more than 2 \\n at the end of file", 2);
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maped.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:33:48 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/15 03:53:15 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "c_maths.h"

void		print_the_map(t_matrix ***map)
{
	int	i;
	int	j;

	j = 0;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
			dprintf(1, "%f	", map[j][i]->m[Y]);
			i++;
		}
		dprintf(1, "\n");
		j++;
	}
	dprintf(1, "\n\n\n\n\n");
//	sleep(10);
}


t_matrix	***get_map(double *z_max, double *z_min)
{
	t_matrix	***map_mat;
	int			x;
	int			y;
	int			i;
	int			j;
//	double		z_max;
//	double		z_min;

//	dprintf(1, "D\n");
	int			tab2[10][10]		=	{{0, 0, 0,-0,-0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{-0, 0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0,-0, 0, 0, 0,-0, 0, 0,-0, 0},
										{ 0,-0,-0, 0,-0, 0, 0, 0,-0,-0},
										{-0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
										{ 0,-0,-0, 0, 0, 0, 0, 0, 0, 0},
										{ 0, 0, 0, 0, 0, 0,-0, 0, 0, 0},
										{-0,-0, 0, 0,-0, 0, 0, 0, 0, 0},
										{ 0, 0, 0,-0, 0,-0, 0, 0, 0, 100}};

	int			tab1[10][10]	=	{{-6,-67,-61,-38,  9,-16,-16, 32, 56, 16},
									{ 27,-63, 23,-56, 63, 10, 33, -9,-55, 69},
									{-44,-23,-58, 12,-55,  0, 21,-25, 27, 48},
									{  1, 41,-38, 57, 38,-17,-50, -2,-63, 7},
									{ 32,-46,-11, 30, 10, 13,-48,-37, 66,-53},
									{-54, 34, 51,-40,-33, 52,-62,-37,-54,-9},
									{-58, 40,-30, -9, 59,  7,-66,-12,-18, 41},
									{-50, 67, 36, 13, 12, -2,-28, 10,-60,-58},
									{  3,-27,-52, 56, 26,-52, 59,-31,-48,-6},
									{-59,-30, 50, 36,  5,-11,  0, 60,-24,-34}};

	(void)tab2;
	(void)tab1;
	x = 10;
	y = 10;
	if (!(map_mat = (t_matrix***)malloc(sizeof(t_matrix**) * y)))
		return (NULL);
	j = 0;
	while (j < y)
	{
		i = 0;
		if (!(map_mat[j] = (t_matrix**)malloc(sizeof(t_matrix*) * x)))
			return (NULL);
		while (i < x)
		{
			if (!(map_mat[j][i] = matrix_init(1, 4)))
				return (NULL);
			*z_max = MAX(tab2[j][i], *z_max);
			*z_min = MIN(tab2[j][i], *z_min);
			matrix_buffer(map_mat[j][i]);
			matrix_put_in((i - 5) * 30, (j - 5) * 30, tab2[j][i] / 2, 1);
			i++;
		}
		j++;
	}
//	dprintf(1, "F\n");
//	print_the_map(map_mat);
	return (map_mat);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/16 01:06:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

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
//	dprintf(1, "x:%d y:%d  color:%d\n", x, y, color);
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
	if ( x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y)
	{
//		dprintf(1, "x_max:%d y_max:%d\n", e->size_line  / 4, 990);
//		dprintf(1, "out of window x:%d y:%d\n", x, y);
		return ;
	}
	r = (int) pos_color->m[3] + 0.5;
	g = (int) pos_color->m[4] + 0.5;
	b = (int) pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
//	dprintf(1, "======= YEAHHHH BABY  ====== x:%d y:%d  r:%d v:%d b:%d ilne:%d\n", x, y, r, g, b, e->size_line);
}

void	string_put(char *s1, char *s2, t_env *e, int y)
{
	char *str;

	str = ft_strnew(60);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	mlx_string_put(e->mlx, e->win, 1200, y, 0xFFFF00, str);
}

void	print_state(t_env *e)
{
	char	*str;

	string_put("Zoom : ", ft_itoa(e->zoom), e, 50);
	(e->proj == 0) ? str = ft_strdup("isometric") : (void)e->proj;
	(e->proj == 1) ? str = ft_strdup("parallel") : (void)e->proj;
	(e->proj == 2) ? str = ft_strdup("conic") : (void)e->proj;
	string_put("Projection : ", str, e, 60);
	ft_strdel(&str);
	string_put("Offset X : ", ft_itoa(e->decalx), e, 70);
	string_put("Offset Y : ", ft_itoa(e->decaly), e, 80);
	str = ft_strnew(20);
	str = ft_strcat(str, " R = ");
	str = ft_strcat(str, ft_itoa((int)e->r));
	str = ft_strcat(str, " G = ");
	str = ft_strcat(str, ft_itoa((int)e->g));
	str = ft_strcat(str, " B = ");
	str = ft_strcat(str, ft_itoa((int)e->b));
	string_put(str, "", e, 90);
	ft_strdel(&str);
}

void	env(int **map)
{
	t_env	e;

	e.map = map;
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_Y, SIZE_X, "sandwich");
	e.img = mlx_new_image(e.mlx, SIZE_Y, SIZE_X);
	e.data = mlx_get_data_addr(e.img, &e.depth, &e.size_line, &e.endian);
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	e.size_map_x = 10;	
	e.size_map_y = 10;	
	e.ecr_x = SIZE_X;
	e.ecr_y = SIZE_Y;
	e.proj = 0;
	e.scale = 2.5;
	e.cte1 = 0.6;
	e.zoom = 8;
	e.decalx = 150;
	e.decaly = 150;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	e.rot_x = 0;
	e.rot_y = 0;
	e.rot_z = 0;
	e.cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 *M_PI, &e);
	init_t_key(&e.key);
	mlx_hook(e.win, 2, 1, key_press, &e);
	mlx_hook(e.win, 3, 2, key_release, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:44:11 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/10 09:38:04 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
# define BUFFER 100

/*
int		fill_mapstr(t_list **begin, int *nbr)
{
	int		oct_lu;
	t_list	*elem;
	t_list	*prev;


	if (!begini || !*begin
			|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * BUFFER), 0)))
		return (0);
	*begin = elem;
	oct_lu = read(fd, elem->content, BUFFER);
	*nbr += oct_lu;
	elem->content_size = oct_lu;
	while (oct_lu == BUFFER)
	{
		prev = elem;
		if (!(elem = ft_lstnew((char*)malloc(sizeof(char) * BUFFER), 0))
			|| oct_lu = read(fd, elem->content, BUFFER) < 0)
			return (0);
		elem->content_size = oct_lu;
		prev->next = elem;
	}
	return (1);
}

char	*malloc_str(t_list	*data, size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	while (data)
	{
		ft_memamove(str, data->content, data->content_size);
		data = data->next;
		str += data->content_size;
	}
	return (str);
}

int		fill_line(char *str, t_list **begin)
{
	int		nb_ligne;
	int		size;
	t_list	*elem;
	t_list	*prev;


	nb_ligne = 0;
	if (!str || !begini || !*begin 
		|| !(size = ft_strchr((char*)*(begin)->content, '\n'))
		|| !(size = ft_strlen((char*)*(begin)->content))
		|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * size), size)))
		return (-1);
	*begin = elem;
	ft_memmove(elem->content, str, size);
	str += size;
	while (oct_lu == BUFFER)
	{
		prev = elem;
		if (!(size = ft_strchr((char*)*(begin)->content, '\n'))
			|| !(size = ft_strlen((char*)*(begin)->content))
			|| !(elem = ft_lstnew((char*)malloc(sizeof(char) * size), size)))
			return (0);
		prev->next = elem;
		ft_memmove(elem->content, str, size);
		str += size;
		nb_ligne++;
	}
	return (nb_ligne);
}

t_matrix	**fill_the_real_map(int	x, int y)
{
	t_matrix	***map;
	int			j;

	***map = (t_matrix***)malloc(sizeof(t_matrix**) * y);
	j = 0;
	while (j < y)
	{
		**map = (t_matrix**)malloc(sizeof(t_matrix*) * x);
		i = 0;
		while ();
		j++;
	}
}

//	on recupere une chaine de caractere
//	on rend chanque ligne dans des liste
//	on malloque le tbleaud e table
//	on le remplis avec la piste
//	count word/ cheque if 
*/
int						parse(int fd)
{
	int		map;
	t_list	*begin;

	(void)map;
	(void)fd;
	(void)begin;
	return (1);
}
//*/
//	on 
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paseur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 05:35:40 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/10 09:38:05 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	on recupere tout un fichier
//	on le decoupe en mot et en ligne
//		si il y a autre chose que des nombre
//		ou que la map n'est pas un rectangle
//			on quite
//
//
//	ft_atoi_base magic
//	on definie la camera
//	on fait les projection
//	on deplace la camera
//	on gere les couleur joliment (luminosite si loin)
//	on prend 2  map en entrer et on fait un plafond (ou carrement autant de sole que l'on veux)


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/15 11:24:00 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
t_matrix **init_tabmat()
{
	int			i;
	t_matrix	**point;

	if (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 4)))
	i = 0;
	whil (i < 4)
	{
		if (!(point[i] = matrix_put_in_new(0, 0, 0, 1)))
				return (NULL);
		i++;
	}
	return (point);
}
*/

void	define_color(t_matrix *point, t_matrix *color)
{
	if (point && color)
	{
		color->m[R] = 100;
		color->m[G] = 100;
		color->m[B] = 128 - 2 * point->m[Z];
	}
	else
		;//dprintf(1, "							NO COLOR SET\n");
}

void	get_point(t_matrix ***map, t_matrix **point, int i, int j)
{
	int	k;

//	dprintf(1, "OUI\n");
	if (!(point[0] = (i < 10 && j < 10) ? matrix_copy(map[j][i]) : NULL))
		;//dprintf(1, "0=>no pt[%d][%d]\n", j, i);
//	dprintf(1, "OUI\n");
	if (!(point[1] = (i < 9 && j < 10) ? matrix_copy(map[j][i + 1]) : NULL))
		;//dprintf(1, "1=>no pt[%d][%d]\n", j, i+1);
//	dprintf(1, "OUI\n");
	if (!(point[2] = (j < 9 && i < 10) ? matrix_copy(map[j + 1][i]) : NULL))
		;//dprintf(1, "2=>no pt[%d][%d]\n", j+1, i);
//	dprintf(1, "OUI\n");
	if (!(point[3] = (j < 9 && i < 9) ? matrix_copy(map[j + 1][i + 1]) : NULL))
		;//dprintf(1, "3=>no pt[%d][%d]\n", j+1, i+1);
//	dprintf(1, "OUI\n");
	k = 0;
	while (k < 4)
	{
//	dprintf(1, "NON\n");
		if (point[k])
			define_color(point[k], point[k + 4]);
		else
			point[k] = NULL;
		k++;
	}
	//dprintf(1, "OOO\n");
}

void	draw_link(t_env *e, t_cam *cam, t_matrix **pt)
{
	(void)cam;
	if (pt[0] && pt[0]->m[Z] > 0)
	{
//		matrix_display(pt[0]);
		if (pt[1] && pt[1]->m[Z] > 0)
		{
//			matrix_display(pt[1]);
			draw_line(e, init_mat_line(pt[0], pt[1], pt[4], pt[5]));
		}
		else
		;//	dprintf(1, "draw_link no 1\n");
		if (pt[2] && pt[2]->m[Z] > 0)
		{
//			matrix_display(pt[2]);
			draw_line(e, init_mat_line(pt[0], pt[2], pt[4], pt[6]));
		}
		else
		;//	dprintf(1, "draw_link no 2\n");
		if (pt[3] && pt[3]->m[Z] > 0)
		{
//			matrix_display(pt[3]);
			draw_line(e, init_mat_line(pt[0], pt[3], pt[4], pt[7]));
		}
		else
		;//	dprintf(1, "draw_link no 3\n");
	}
	else
	;//	dprintf(1, "draw_link no 0\n");
}

//*
void	iso_proj(t_cam *cam, t_matrix *rot, t_matrix *pt)
{
	double	mult;
	double	dx;
	double	dy;

	double	x, y;

	(void)x;
	(void)y;
	t_matrix	*o;
	t_matrix	*hrz;
	t_matrix	*vert;
	rot  = set_rotate(cam->rot->m[X], cam->rot->m[Y], cam->rot->m[Z]);
	/*
	double	x_max;
	double	y_min;
	double	y_max;
	*/
(void)dx;
(void)dy;
(void)mult;
(void)pt;
(void)cam;
(void)hrz;
(void)vert;

/*
 
	pt->m[X] = cam->pos->m[X];
	pt->m[Y] = cam->pos->m[Y];
	pt->m[X] *= (SIZE_Y / (2 * mult));
	pt->m[Y] *= (SIZE_Y / (2 * mult));
	

	pt->m[X] += SIZE_Y / 2;
	pt->m[Y] += SIZE_X / 2;

	(void)rot;

 *
 * */

//	pt = matrix_product(rot, pt);
//	pt = matrix_product(rot, pt);
	mult = pt->m[Z] - cam->pos->m[Z];
	dx = (mult * (cam->corner[2]->m[X] - cam->corner[1]->m[X]));
	dy = (mult * (cam->corner[0]->m[Y] - cam->corner[1]->m[Y]));

	o = matrix_scalar_product_new(cam->corner[1], 1);	
//	x = ((pt->m[X]) - (o->m[X]));
//	y = ((pt->m[Y]) - (o->m[Y]));
//	x = x / mult;
//	y = y / mult;
//	x = (x / dx) * SIZE_Y;
//	y = (y / dy) * SIZE_X;
	x = ((pt->m[X] - cam->pos->m[X]) / mult) * SIZE_Y / 2;
	y = ((pt->m[Y] - cam->pos->m[Y]) / mult) * SIZE_X / 2;
	(void)rot;
	pt->m[X] = (x);
	pt->m[Y] = (y);
	/*
	matrix_display(pt);
	write(1, ".\n", 2);
	pt = matrix_product(rot, pt);
	matrix_display(rot);
	write(1, ".\n", 2);
	matrix_display(pt);
	write(1, "\n\n\n", 3);
	*/
//	pt = matrix_product(rot, pt);
//	matrix_display(rot);
	
//	pt->m[X] += SIZE_Y / 2;
//	pt->m[Y] += SIZE_X / 2;

//	matrix_product_in(rot, pt, pt);
//	pt->m[X] -= (cam->pos->m[X] + (cam->corner[1]->m[X] * mult));
//	pt->m[Y] -= (cam->pos->m[Y] + (cam->corner[1]->m[Y] * mult));

//	pt->m[X] += o->m[X];
//	pt->m[Y] += o->m[Y];
//	matrix_add_in(o, cam->pos, o);
	o = matrix_add(o, cam->pos);

//	hrz = matrix_sub(cam->corner[2], cam->corner[1]);	
//	hrz = matrix_scalar_product(, mult);
//	vert = matrix_sub(cam->corner[0], cam->corner[1]);	
//	vert = matrix_scalar_product(y, mult);

//	0 = matrix_initcam->corner[1]
//	pt->m[Y] -= ;
//	pt->m[Z] -= ;
	/*
	mult = pt->m[Z];
	dx = SIZE_Y / ((cam->corner[2]->m[X] - cam->corner[1]->m[X]) * mult);
	dy = SIZE_X / ((cam->corner[0]->m[Y] - cam->corner[1]->m[Y]) * mult);
	pt->m[X] = (pt->m[X] - cam->corner[1]->m[X]) * dx;
	pt->m[Y] = (pt->m[Y] - cam->corner[1]->m[Y]) * dy;
	//	le vecteur (BD-BG)
	//	le vecteur (HG-BG)
*/
}
//*/

void	adapt_point(t_cam *c, t_matrix ***pt, int size_x, int size_y)
{
	int					i;
	int					j;
	static	t_matrix	*tmp = NULL;
	t_matrix			*rot;


	double	x, y, z, mult;
	x = 1;
	y = 1;
	z = 1;
	mult = 0;
	if (!c)
		dprintf(1, "adapt_point no c\n");
	if (!pt)
		dprintf(1, "adapt_point no pt \n");
	if (!*pt)
		dprintf(1, "adapt_point no pt*\n");
	if ((!tmp && (tmp = matrix_init(1, 4)))
		|| !(rot = set_rotate(c->rot->m[X] * x, c->rot->m[Y] * y,  c->rot->m[Z] * z)))
		return ;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			//	la il faudrait soustraire la pose de la cam
//			matrix_sub_in(c->pos, pt[j][i], pt[j][i]);
		//	pt[j][i]->m[X] -= c->pos->m[X];
	//		pt[j][i]->m[Y] -= c->pos->m[Y];
//			pt[j][i]->m[Z] -= c->pos->m[Z];
//
//			(pt[j][i]) = matrix_product(rot, pt[j][i]);

//*	


//	(pt[j][i]) = matrix_product(rot, pt[j][i]);

//	(pt[j][i]) = matrix_product(rot, pt[j][i]);


	z = pt[j][i]->m[Z] - (1 * c->pos->m[Z]);
	x = ((pt[j][i]->m[X] - (1 * c->pos->m[X])));
	y = ((pt[j][i]->m[Y] - (1 * c->pos->m[Y])));



	pt[j][i]->m[X] = x;
	pt[j][i]->m[Y] = y;
	pt[j][i]->m[Z] = z;


	(pt[j][i]) = matrix_product(rot, pt[j][i]);

	z = pt[j][i]->m[Z] - (1 * c->pos->m[Z]);
	x = ((pt[j][i]->m[X] - (1 * c->pos->m[X])));
	y = ((pt[j][i]->m[Y] - (1 * c->pos->m[Y])));



	x *= SIZE_Y / (2 * z);
	y *= SIZE_X / (2 * z);


	pt[j][i]->m[X] = x;
	pt[j][i]->m[Y] = y;
	pt[j][i]->m[Z] = z;



//	pt[j][i]->m[X] = x;
//	pt[j][i]->m[Y] = y;
//	pt[j][i]->m[Z] = mult;


//	(pt[j][i]) = matrix_product(rot, pt[j][i]);

//*/
//			iso_proj(c, rot, pt[j][i]);

			pt[j][i]->m[X] += SIZE_Y / 2;
			pt[j][i]->m[Y] += SIZE_X / 2;

			if (pt[j][i]->m[Z] - c->pos->m[Z]< 0)
			{
				dprintf(1, "	is out i:%d	j:%d\n", i, j);
				matrix_display(pt[j][i]);
				write(1, "\n\n", 2);
			}
			i++;
		}
		j++;
	}	
}

void	free_point(t_matrix ***pt, int size_x, int size_y)
{
	int					i;
	int					j;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			matrix_free(pt[j] + i);
			i++;
		}
		j++;
	}	
}

int		init_color(t_matrix **point)
{
	int	i;

	i = 4;
	while (i < 8)
	{
		if (!(point[i] = matrix_init(1, 4)))
			return (0);
		i++;
	}
	return (1);
}

void	print_map(t_env *e, t_cam *cam, t_matrix ***map)
{
	int					i;
	int					j;
	static	t_matrix	**point = NULL;
//	static	t_matrix	**color = NULL;

	if (!cam)
		dprintf(1, "print_map	no cam\n");
	if (!map)
		dprintf(1, "print_map	no map\n");
	if (!*map)
		dprintf(1, "print_map	no *map\n");
	if (!**map)
		dprintf(1, "print_map	no **map\n");

	adapt_point(cam, map, e->size_map_x, e->size_map_y);
	j = 0;
	if ((!point && (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))
		|| !init_color(point))))
		return ;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
		//	matrix_display(map[j][i]);
//			dprintf(1, "i: %d	j:%d\n", i, j);
		//	if (i >= 8 && j == 9)
//				dprintf(1, "i:%d j:%d\n", i, j);
			get_point(map, point, i, j);
//	dprintf(1, "voulou\n");
//	dprintf(1, "voulou\n");
			draw_link(e, cam, point);
	//		if (i >= 8 && j == 9)
	//			dprintf(1, "end\n");
//(void)e;
//	dprintf(1, "voulou\n");
			i++;
		}
		j++;
	}
	free_point(map, e->size_map_x, e->size_map_y);

}

//	void	draw_line(t_env *e, t_matrix *mat_line)
//	t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2)
