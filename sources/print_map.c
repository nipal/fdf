/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 03:54:36 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/13 06:13:55 by fjanoty          ###   ########.fr       */
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

int		is_visible(t_matrix **corner, t_matrix *pt)
{
	int		i;
	double	result;

	i = 0;

	if (pt->m[Z] < 0)
	{
//		dprintf(1, "is out minus\n");
		return 0;
	}
	while (i < 4)
	{

		if ((result = matrix_dot_product(corner[i], pt)) == 0)
		{
//			dprintf(1, "is out :%d\n", i);
//		dprintf(1, "i%d\n", i);
//		matrix_display(pt);
//		matrix_display(corner[i]);
//		dprintf(1, "result:%f\n", result);

			return (0);;
		}
//		dprintf(1, "i%d\n", i);
//		matrix_display(pt);
//		matrix_display(corner[i]);
//		dprintf(1, "result:%f\n", result);
		i++;
	}
	return (1);
}

void	draw_link(t_env *e, t_cam *cam, t_matrix **pt)
{
	if (pt[0] && is_visible(cam->corner, pt[0]))
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


	//*
	matrix_display(pt);
	write(1, ".\n", 2);
	pt = matrix_product(rot, pt);
	matrix_display(rot);
	write(1, ".\n", 2);
	matrix_display(pt);
	write(1, "\n\n\n", 3);
//	*/


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

/*
	(pt[j][i]) = matrix_product(rot, pt[j][i]);

	z = pt[j][i]->m[Z] - (1 * c->pos->m[Z]);
	x = ((pt[j][i]->m[X] - (1 * c->pos->m[X])));
	y = ((pt[j][i]->m[Y] - (1 * c->pos->m[Y])));

*/

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

//			pt[j][i]->m[X] += SIZE_Y / 2;
//			pt[j][i]->m[Y] += SIZE_X / 2;

			if (pt[j][i]->m[Z] - c->pos->m[Z]< 0)
			{
		//		dprintf(1, "	is out i:%d	j:%d\n", i, j);
		//		matrix_display(pt[j][i]);
		//		write(1, "\n\n", 2);
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

//	
void	print_map(t_env *e, t_cam *cam, t_matrix ***map)
{
	int					i;
	int					j;
	static	t_matrix	**point = NULL;
//	static	t_matrix	**color = NULL;

	if (!cam || !map || !*map || !**map)
	{
		dprintf(1, "error\n");
		return ;
	}

//	adapt_point(cam, map, e->size_map_x, e->size_map_y);
	dprintf(1, "  $	F\n");
	j = 0;
	if ((!point && (!(point = (t_matrix**)malloc(sizeof(t_matrix*) * 8))
		|| !init_color(point))))
		return ;
	dprintf(1, "  $	G\n");
	while (j < e->size_map_y)
	{
		dprintf(1, "    $	H [%d]\n", j);
		i = 0;
		while (i < e->size_map_x)
		{
//			dprintf(1, "    $	I\n");
		//	matrix_display(map[j][i]);
//			dprintf(1, "i: %d	j:%d\n", i, j);
		//	if (i >= 8 && j == 9)
//				dprintf(1, "i:%d j:%d\n", i, j);
//			get_point(map, point, i, j);
//			dprintf(1, "    $	J\n");
//	dprintf(1, "voulou\n");
//	dprintf(1, "voulou\n");
			if (i == 9 && j == 9)
			{
//				matrix_display(map[j][i]);
			}
//			dprintf(1, "    $	K\n");
//			draw_link(e, cam, point);
//			dprintf(1, "    $	L\n");
	//		if (i >= 8 && j == 9)
	//			dprintf(1, "end\n");
//(void)e;
//	dprintf(1, "voulou\n");
			i++;
		}
		dprintf(1, "    $	______\n");
		j++;
	}
//	free_point(map, e->size_map_x, e->size_map_y);

	dprintf(1, "  $	M\n");
}

//	void	draw_line(t_env *e, t_matrix *mat_line)
//	t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2)
