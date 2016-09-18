/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/30 14:38:59 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/18 06:20:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

void	adapt_point(t_cam *c, t_matrix ***pt, int size_x, int size_y);

void	draw_line(t_env *e, t_matrix *mat_line)
{
	int			i;
	int			size;
	t_matrix	*diff;
	t_matrix	*org;
	t_matrix	*print;

//	dprintf(1, "\n");
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
//	matrix_free(&diff);
//	matrix_free(&print);
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
	//	return (NULL);
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

	if (!(pt = matrix_init(3, 1)))
		return (NULL);
	a = rot % size == rot % (size * 2);
	b = rot % (size * 2) == rot % (size * 4);
	val = rot % size;
	pt->m[2] = 0;
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
	
	if (!(pt1 = matrix_init(3, 1))
		|| !(color = matrix_init(3, 1))
		|| !(color2 = matrix_init(3, 1))
		|| !(color3 = matrix_init(3, 1))
		|| !(pt2 = matrix_init(3, 1))
		|| !(pt4 = matrix_init(3, 1))
		|| !(pt5 = matrix_init(3, 1))
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
	{
		dprintf(1, "\n\nAll is well 2\n");
	}
	else
	{
		draw_line(e, mat_line);
		matrix_free(&mat_line);
	}



	if (!(mat_line = init_mat_line(pt4, pt1, color2, color)))
	{
		dprintf(1, "All is well 3\n");
	}
	else
	{
		draw_line(e, mat_line);
		matrix_free(&mat_line);
	}

	//draw_line(e, mat_line);

	if (!(mat_line = init_mat_line(pt1, pt5, color, color3)))
	{
		dprintf(1, "All is well 3\n");
	}
	else
	{
		draw_line(e, mat_line);
		matrix_free(&mat_line);
	}
//	draw_line(e, (mat_line));
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
}

//	ca c'est un peu la boucle principale
//void	(t_env *e)

/*######################################################*/
/*######################################################*/

//void	write_map(t_matrix	***map);
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
	//	On veu reduire x et y en fonction de z
	//		-on va le faire autoure de 0
	//		ou autoure du centre de l'ecran ...
	double	norme;

//	norme = sqrt(matrix_dot_product(vect, vect));
//	norme /= 300;
	norme = vect->m[2] / 500;
	vect->m[0] /= norme;
	vect->m[1] /= norme;
//	vect->m[2] /= norme;
//	dprintf(1, " nrm[%lf]{%lf, %lf}	", norme, vect->m[0], vect->m[1]);
}

void	base_change(t_env *e, t_cam *cam, t_matrix	***map)
{
	int	i;
	int	j;
	t_matrix	*tmp;
	//	t_matrix	*diff;
	t_matrix	*rot;
	
	j = 0;
//	dprintf(1, "angle:\n");
//	matrix_display(cam->rot);
	if (!(rot = set_rotate(cam->rot->m[0], cam->rot->m[1], cam->rot->m[2])))
	{
		dprintf(1, "no  =malloc bitch!");
	}
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			tmp = matrix_product(rot, map[j][i]);
			matrix_sub_in(tmp, cam->pos, tmp);
			conique_adapte(tmp);
//			matrix_free(&map[j][i]);
//			
			map[j][i] = tmp;
//t_matrix		*matrix_product(t_matrix *a, t_matrix *b);
			i++;
		}
		j++;
	}
}

int		is_out(t_matrix *vect, t_env *e)
{
	if (vect->m[0] < e->ecr_x * -0.5 || vect->m[0] > e->ecr_x * 0.5 || vect->m[1] < e->ecr_y * -0.5 || vect->m[1] > e->ecr_y * 0.5 || vect->m[2] < 0)
		return (1);
	return (0);
}

void	draw_link_map(t_env *e)
{
	int			j;
	int			i;
	t_matrix	*mat_line;
	t_matrix	*colore;
	t_matrix	*colore2;
	t_matrix	***map;

	colore = vect_new_vertfd(100, 100, 100);
	colore2 = vect_new_vertfd(200, 200, 200);
	map = e->vect_map;
	j = 0;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)	
		{
//				dprintf(1, "	(A%d,%d){%f:%f:%f}\n", j, i, map[j][i]->m[0], map[j][i]->m[1], map[j][i]->m[2]);
			if (i > (e->size_map_x - 2))
				;//dprintf(1, "\n\nAll is well 1\n");
			else if(!(mat_line = init_mat_line(map[j][i], map[j][i + 1], colore, colore2)))
				dprintf(1, "\n\nAll is well 2\n");
			else if ((is_out(map[j][i], e) || is_out(map[j][i + 1], e)))
			{
				;//dprintf(1, "\n\nAll is well 3\n");
			}
			else
			{
//				dprintf(1, "size_x:%d", e->size_map_x);
//				dprintf(1, "	(B%d,%d)", j, i + 1);dprintf(1, "	{%f:%f:%f}", map[j][i + 1]->m[0], map[j][i + 1]->m[1], map[j][i + 1]->m[2]);
				draw_line(e, mat_line);
//				matrix_free(&mat_line);
			}	
			if (j > (e->size_map_y - 2))
				;//dprintf(1, "\n\nAll is well A\n");
			else if (!(mat_line = init_mat_line(map[j][i], map[j + 1][i], colore, colore2)))
				dprintf(1, "\n\nAll is well B\n");
			else if ((is_out(map[j][i], e) || is_out(map[j + 1][i], e)))
			{
				;//dprintf(1, "\n\nAll is well C\n");
			}
			else
			{
//				dprintf(1, "size_y:%d", e->size_map_y);
//				dprintf(1, "	(B%d,%d)", j + 1, i);dprintf(1, "	{%f:%f:%f}", map[j][i + 1]->m[0], map[j][i + 1]->m[1], map[j][i + 1]->m[2]);
//				dprintf(1, "	(A){%f:%f:%f}", map[j][i]->m[0], map[j][i]->m[1], map[j][i]->m[2]);
//				dprintf(1, "	(C%d,%d){%f:%f:%f}", j, i,map[j + 1][i]->m[0], map[j + 1][i]->m[1], map[j + 1][i]->m[2]);
				draw_line(e, mat_line);
//				matrix_free(&mat_line);
			}	
//			dprintf(1, "G\n");
			i++;
		}
		j++;
	}
//	dprintf(1, "	__--__--__--__	[AFTER] draw-link_map\n");
	(void)e;
}


/*######################################################*/
/*######################################################*/

/*######*/				/*######*/

/*#############*/

/*######################################################*/
/*######################################################*/
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
void	main_work(t_env *e)
{
	// On veux juste tracer la map
//	double	z_max;
//	double	z_min;
	//(void)e;

	t_matrix ***map = get_map(e);
//	t_matrix ***map = copy_vect_map(e);//get_map(e);
	(void)map;
	//	DONE	la on veux pouvoir afficher numeriquement la carte genre sur x, y ou z
	//	DONE	puis avoir une camera 
	//	DONE	puis faire le changement de base
	//	DONE	puis afficher le resulta graphique
	//	DONE	puis gere la distance
	//	DONE	puis afficher le resulta graphique
	
	//	faire iun peutiot scaling en fonction des dimention (x, y, z)
	//	rendre un peu plus propre les truc des angle, mais auttan ca va
	//	mapper des touche pour faire :
	//		{rotation, translation} -->	la camera
	//								-->	l'objet

	//	faire les rotation et la translation + acceleration sur la camera

	//	dprintf(1, "map:%ld\n", (long)map);
	//	dprintf(1, "*map:%ld\n", (long)*map );
	//	dprintf(1, "**map:%ld\n", (long)**map);
	//map;
	//	dprintf(1, "#	1\n");
	//	dprintf(1, "###################################################\n");
	t_cam	*cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 * M_PI, e);
//	describe_cam(cam);
	e->cam = cam;
	if (!e->cam)
		dprintf(1, "Ther is no cam!!!\n");
//	dprintf (1, "%ld\n", (long)e->cam);
	base_change(e, cam, map);
	e->vect_map = map;
	draw_link_map(e);
	//	print_map(e, e->cam, e->vect_map);
	//	dprintf(1, "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	//	dprintf(1, "#	4\n");

		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	//	dprintf(1, "#	5\n");
	//	print_state(e);
	//	(void)cam;
	//	(void)e;
		mlx_do_sync(e->mlx);
}
