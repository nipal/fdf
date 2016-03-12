/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/12 12:54:08 by fjanoty          ###   ########.fr       */
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
		color->m[R] = 10 * point->m[X] + 100;
		color->m[G] = 10 * point->m[Y] + 100;
		color->m[B] = 10 * point->m[Z] + 100;
	}
}

void	get_point(t_matrix ***map, t_matrix **point, int i, int j)
{
	int	k;

/*
	if (!map)
		dprintf(1, "no map1\n");
	else if (!*map)
		dprintf(1, "no map2\n");
	else if (!**map)
		dprintf(1, "no map3\n");
	if (!map || !*map || !**map)
		return;
	else
		dprintf(1, "	HE IS ALIVE\n");
*/
//	dprintf(1, "OUI\n");
	point[0] = (i < 10 && j < 10) ? map[j][i] : NULL;
//	dprintf(1, "OUI\n");
	point[1] = (i < 9 && j < 10) ? map[j][i + 1] : NULL;
//	dprintf(1, "OUI\n");
	point[2] = (j < 9 && i < 10) ? map[j + 1][i] : NULL;
//	dprintf(1, "OUI\n");
	point[3] = (j < 9 && i < 9) ? map[j + 1][i + 1] : NULL;
//	dprintf(1, "OUI\n");
	k = 0;
	while (k < 4)
	{
//	dprintf(1, "NON\n");
		define_color(point[k], point[k + 4]);
		k++;
	}
//	dprintf(1, "OOO\n");
}

void	draw_link(t_env *e, t_matrix **pt)
{
	if (pt[0])
	{
		if (pt[1])
			draw_line(e, init_mat_line(pt[0], pt[1], pt[4], pt[5]));
		else
			dprintf(1, "draw_link no 1\n");
		if (pt[2])
			draw_line(e, init_mat_line(pt[0], pt[2], pt[4], pt[6]));
		else
			dprintf(1, "draw_link no 2\n");
		if (pt[3])
			draw_line(e, init_mat_line(pt[0], pt[3], pt[4], pt[7]));
		else
			dprintf(1, "draw_link no 3\n");
	}
	else
		dprintf(1, "draw_link no 0\n");
}

void	adapt_point(t_cam *c, t_matrix **pt)
{
	int					i;
	static	t_matrix	*tmp = NULL;
	t_matrix			*rot;

	if (!c)
		dprintf(1, "adapt_point no c\n");
	if (!pt)
		dprintf(1, "adapt_point no pt \n");
	if (!*pt)
		dprintf(1, "adapt_point no pt*\n");
	if (!c || (!tmp && (tmp = matrix_init(4, 1)))
		|| !(rot = set_rotate(c->rot->m[X], c->rot->m[Y], c->rot->m[Z])))
		return ;
	i = 0;
	while (i < 4)
	{
		matrix_sub_in(pt[i], c->pos, tmp);
		matrix_product_in(tmp, rot, pt[i]);
		
		//	on divise le point par la distance, et on le multiplie par la resolution
		//	on change de base ==> isometrique
		//	on test si dans l'ecran, on proportionne ===> conique
		i++;
	}
}

void	print_map(t_env *e, t_cam *cam, t_matrix ***map)
{
	int					i;
	int					j;
	static	t_matrix	**point = NULL;
//	static	t_matrix	**color = NULL;

	if (!cam)
		dprintf(1, "print_map	cam\n");
	if (!map)
		dprintf(1, "print_map	map\n");
	if (!*map)
		dprintf(1, "print_map	*map\n");
	if (!**map)
		dprintf(1, "print_map	**map\n");

	j = 0;
	if ((!point && !(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))))
		return ;
	while (j < 10)
	{
		i = 0;
		while (i < 10)
		{
//			matrix_display(map[j][i]);
//			dprintf(1, "i: %d	j:%d\n", i, j);
			get_point(map, point, i, j);
//	dprintf(1, "voulou\n");
			adapt_point(cam, point);
//	dprintf(1, "voulou\n");
			draw_link(e, point);
//	dprintf(1, "voulou\n");
			i++;
		}
		j++;
	}
}

//	void	draw_line(t_env *e, t_matrix *mat_line)
//	t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2)
