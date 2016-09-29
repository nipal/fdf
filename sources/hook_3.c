/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:52:27 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/29 23:40:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

/*
**	ft_putchar('[');
** 	ft_putnbr(keycode);
**	ft_putstr("] ");
*/

void	key_release_end(int keycode, t_env *e)
{
	(keycode == 53) ? e->key.echap = 0 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 0 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 0 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 0 : (void)keycode;
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
}

int		key_release(int keycode, t_env *e)
{
	(keycode == 6) ? e->key.fi1 = 0 : (void)keycode;
	(keycode == 7) ? e->key.fi_1 = 0 : (void)keycode;
	(keycode == 8) ? e->key.fi2 = 0 : (void)keycode;
	(keycode == 9) ? e->key.fi_2 = 0 : (void)keycode;
	(keycode == 27) ? e->key.speed_down = 0 : (void)keycode;
	(keycode == 24) ? e->key.speed_up = 0 : (void)keycode;
	(keycode == 29) ? e->key.speed_stop = 0 : (void)keycode;
	(keycode == 13) ? e->key.rot_x1 = 0 : (void)keycode;
	(keycode == 12) ? e->key.rot_y1 = 0 : (void)keycode;
	(keycode == 0) ? e->key.rot_z1 = 0 : (void)keycode;
	(keycode == 1) ? e->key.rot_x2 = 0 : (void)keycode;
	(keycode == 14) ? e->key.rot_y2 = 0 : (void)keycode;
	(keycode == 2) ? e->key.rot_z2 = 0 : (void)keycode;
	(keycode == 32) ? e->key.rot_cam_x1 = 0 : (void)keycode;
	(keycode == 34) ? e->key.rot_cam_y1 = 0 : (void)keycode;
	(keycode == 38) ? e->key.rot_cam_z1 = 0 : (void)keycode;
	(keycode == 31) ? e->key.rot_cam_x2 = 0 : (void)keycode;
	(keycode == 40) ? e->key.rot_cam_y2 = 0 : (void)keycode;
	(keycode == 37) ? e->key.rot_cam_z2 = 0 : (void)keycode;
	key_release_end(keycode, e);
	return (1);
}

int		increm_dir_cam(t_env *e)
{
	t_matrix	*tmp;
	t_matrix	*rot;
	t_matrix	*dir;

	if (!(rot = set_rotate(e->rot_x, e->rot_y, e->rot_z))
		|| (dir = matrix_put_in_new(0, 0, 1, 0)))
		return (0);
	tmp = matrix_product(rot, dir);
	matrix_free(&dir);
	dir = tmp;
	matrix_scalar_product(dir, 0.01 * e->speed);
	e->cam->pos->m[X] += dir->m[X];
	e->cam->pos->m[Y] += dir->m[Y];
	e->cam->pos->m[Z] += dir->m[Z];
	matrix_free(&rot);
	matrix_free(&dir);
	return (1);
}

void	increm_pos_cam(t_env *e)
{
	t_matrix	*move;

	if (!(move = matrix_scalar_product_new(e->cam->base[2], e->speed)))
		return ;
	matrix_add_in(e->cam->pos, move, e->cam->pos);
	matrix_free(&move);
}

void	manage_cam_rot(t_env *e)
{
	int				i;
	t_matrix		*tmp;
	t_matrix		*rot;
	t_matrix		*mat_rot;
	static	double	deg = 0.03;

	if (!(rot = matrix_init(1, 3)))
		return ;
	(e->key.rot_cam_z2) ? rot->m[2] -= deg : (void)e;
	(e->key.rot_cam_z1) ? rot->m[2] += deg : (void)e;
	(e->key.rot_cam_x2) ? rot->m[0] -= deg : (void)e;
	(e->key.rot_cam_x1) ? rot->m[0] += deg : (void)e;
	(e->key.rot_cam_y2) ? rot->m[1] -= deg : (void)e;
	(e->key.rot_cam_y1) ? rot->m[1] += deg : (void)e;
	if (!(mat_rot = set_rotate(rot->m[0], rot->m[1], rot->m[2])))
		return ;
	i = -1;
	while ((++i < 3) || (matrix_free(&mat_rot) && matrix_free(&rot)))
	{
		if (!(tmp = matrix_product(mat_rot, e->cam->base[i])))
			return ;
		matrix_free(e->cam->base + i);
		e->cam->base[i] = tmp;
	}
}


