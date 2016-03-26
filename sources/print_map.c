/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/25 02:37:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_triangle(t_env *e, t_matrix **pt, t_matrix **cl);

void	define_color(t_matrix *point, t_matrix *color)
{
	if (point && color)
	{
		double	caca = ABS(point->m[X]);
		if (point->m[Y] > 0)
		{
			color->m[R] = 0;
			color->m[G] = caca;
			color->m[B] = 0;
		}
		if (point->m[Y] < 0)
		{
			color->m[R] = 0;
			color->m[G] = 50;
			color->m[B] = caca;
		}
		else
		{
			color->m[R] = caca;
			color->m[G] = 50;
			color->m[B] = 0;
		}
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
			define_color(map[j + 11][i], point[k + 4]);
		else
			point[k] = NULL;
		k++;
	}
	//dprintf(1, "OOO\n");
}

int	is_inside(t_env *e, t_matrix *pt)
{
	double	coef = 1500;
//	if (e)
//		return (1);

	/*
	if (pt->m[Z] < 0 || pt->m[X] < -e->ecr_x / 2 || pt->m[Y] < -e->ecr_y / 2
		|| pt->m[X] > e->ecr_x / 2 || pt->m[Y] > e->ecr_y / 2)
		return (0);
	*/
(void)e;
	if (pt->m[Z] < 0 || pt->m[X] < -coef || pt->m[Y] < -coef
		|| pt->m[X] > coef || pt->m[Y] > coef)
		return (0);
	return (1);
}

void	draw_link(t_env *e, t_cam *cam, t_matrix **pt)
{
	int	one;
	int	two;

	(void)cam;
	if (pt[0])
	{
		one = (is_inside(e, pt[0])) ? 1 : 0 ;
		if (pt[1])
		{
			two = (is_inside(e, pt[1])) ? 1 : 0 ;
			if (one || two)
				draw_line(e, init_mat_line(pt[0], pt[1], pt[4], pt[5]));
		}
		else
		;//	dprintf(1, "draw_link no 1\n");
		if (pt[2])
		{
			two = (is_inside(e, pt[2])) ? 1 : 0 ;
			if (one || two)
			{
				print_line(pt[0], pt[4], pt[2], pt[6]);
			}
		}
		else
		;//	dprintf(1, "draw_link no 2\n");
		if (pt[3])
		{
			two = (is_inside(e, pt[3])) ? 1 : 0 ;
			if (one || two)
				draw_line(e, init_mat_line(pt[0], pt[3], pt[4], pt[7]));
		}
		else
		;//	dprintf(1, "draw_link no 3\n");
	}
	else
	;//	dprintf(1, "draw_link no 0\n");
}



/*
 *	On veux imprimer deux triangle
 * */
//	one = (is_inside(e, pt[0])) ? 1 : 0 ;
void	draw_face(t_env *e, t_matrix **pts)
{
	t_matrix	**pt;
	t_matrix	**cl;

//	pt = NULL;
//	cl = NULL;
		if (pts[0] && pts[1] && pts[2] 
			&& ((is_inside(e, pts[0]))
			&& (is_inside(e, pts[1]))
			&& (is_inside(e, pts[2]))))
		{
			pt = tab_matrix(pts[0], pts[1], pts[2]);
			cl = tab_matrix(pts[4], pts[5], pts[6]);
			print_triangle(e, pt, cl);
		}

		if (pts[1] && pts[2] && pts[3] 
			&& ((is_inside(e, pts[1]))
			&& (is_inside(e, pts[2]))
			&& (is_inside(e, pts[3]))))
		{
			pt = tab_matrix(pts[1], pts[2], pts[3]);
			cl = tab_matrix(pts[5], pts[6], pts[7]);
			print_triangle(e, pt, cl);
		}


		if (pts[2] && pts[3] && pts[0] 
			&& ((is_inside(e, pts[2]))
			&& (is_inside(e, pts[3]))
			&& (is_inside(e, pts[0]))))
		{
			pt = tab_matrix(pts[2], pts[3], pts[0]);
			cl = tab_matrix(pts[6], pts[7], pts[4]);
			print_triangle(e, pt, cl);
		}

		if (pts[3] && pts[0] && pts[1] 
			&& ((is_inside(e, pts[3]))
			&& (is_inside(e, pts[0]))
			&& (is_inside(e, pts[1]))))
		{
			pt = tab_matrix(pts[3], pts[0], pts[1]);
			cl = tab_matrix(pts[7], pts[4], pts[5]);
			print_triangle(e, pt, cl);
		}

/*
		if (pts[1] && pts[2] && pts[3] 
			&& ((is_inside(e, pts[1]))
			&& (is_inside(e, pts[2]))
			&& (is_inside(e, pts[3]))))
		{
			pt = tab_matrix(pts[1], pts[2], pts[3]);
			cl = tab_matrix(pts[5], pts[6], pts[7]);
			print_triangle(e, pt, cl);
		}
		*/
}

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
	mult = 1;
	if (!c)
		dprintf(1, "adapt_point no c\n");
	if (!pt)
		dprintf(1, "adapt_point no pt \n");
	if (!*pt)
		dprintf(1, "adapt_point no pt*\n");
	if ((!tmp && (tmp = matrix_init(1, 4)))
		|| !(rot = set_rotate(c->rot->m[X] * -x, c->rot->m[Y] * -y,  c->rot->m[Z] * -z)))
		return ;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			matrix_sub_in(c->pos, pt[j][i], pt[j][i]);
			(pt[j][i]) = matrix_product(rot, pt[j][i]);

			pt[j][i]->m[X] *= (SIZE_X) / pt[j][i]->m[Z];
			pt[j][i]->m[Y] *= (SIZE_Y) / pt[j][i]->m[Z];
//			matrix_scalar_product(pt[j][i], SIZE_X / (2 * (pt[j][i]->m[Z])));
	//matrix_sub_in(pt[j][i], c->pos, pt[j][i]);

	//pt[j][i] = matrix_product(rot, pt[j][i]);

			pt[j][i]->m[X] += SIZE_X / 2;
			pt[j][i]->m[Y] += SIZE_Y / 2;

			if (pt[j][i]->m[Z] - c->pos->m[Z] < 0)
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

	adapt_point(e->cam, map, e->size_map_x, e->size_map_y);
	j = 0;
	if ((!point && (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))
		|| !init_color(point))))
		return ;
	while (j < e->size_map_y)
	{
		i = 0;
		while (i < e->size_map_x)
		{
			dprintf(1, "i:%d j:%d I:%d, J:%d\n", i, j, e->size_map_y, e->size_map_x);
			get_point(map, point, i, j);
			dprintf(1, "i:%d j:%d I:%d, J:%d\n", i, j, e->size_map_y, e->size_map_x);
			draw_link(e, e->cam, point);
		//	draw_face(e, point);
//			draw_link(e, e->cam, point);
			dprintf(1, "i:%d j:%d I:%d, J:%d\n", i, j, e->size_map_y, e->size_map_x);
			i++;
		}
		j++;
	}
//	free_point(map, e->size_map_x, e->size_map_y);

}

//	void	draw_line(t_env *e, t_matrix *mat_line)
//	t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2)
