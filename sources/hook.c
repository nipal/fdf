/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/15 09:18:09 by fjanoty          ###   ########.fr       */
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
	key->speed_up = 0;
	key->speed_down = 0;
}

int		key_press(int keycode, t_env *e)
{
	(keycode == 78) ? e->key.speed_down = 1 : (void)keycode;
	(keycode == 69) ? e->key.speed_up = 1 : (void)keycode;
	(keycode == 0) ? e->key.rot_z2 = 1 : (void)keycode;
	(keycode == 1) ? e->key.rot_x1 = 1 : (void)keycode;
	(keycode == 2) ? e->key.rot_z1 = 1 : (void)keycode;
	(keycode == 12) ? e->key.rot_y2 = 1 : (void)keycode;
	(keycode == 13) ? e->key.rot_x2 = 1 : (void)keycode;
	(keycode == 14) ? e->key.rot_y1 = 1 : (void)keycode;
	(keycode == 53) ? e->key.echap = 1 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 1 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 1 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 1 : (void)keycode;
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
	(keycode == 78) ? e->key.speed_down = 0 : (void)keycode;
	(keycode == 69) ? e->key.speed_up = 0 : (void)keycode;
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

int		increm_dir_cam(t_env *e)
{
	t_matrix	*rot;
	t_matrix	*dir;

	if(!(rot = set_rotate(e->rot_x, e->rot_y, e->rot_z))
		|| dir = mtrix_put_in_new(0, 0, 1, 0))
		return (0);
	dir = matrix_product(rot, dir);
	matrix_scalar_product(dir, 0.01 * e->speed);
	e->cam->pos->m[X] += dir->m[X];
	e->cam->pos->m[Y] += dir->m[Y];
	e->cam->pos->m[Z] += dir->m[Z];
	matrix_free(&rot);
	matrix_free(&dir);
	return (1);
}

int		loop_hook(t_env *e)
{
	static	double	increm = 0.03;
	
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
	(e->key.speed_up == 1) ? e->speed += increm_dir_cam(e) : (void)e;
	(e->key.speed_down == 1) ? e->speed -= increm_dir_cam(e) : (void)e;
	ft_bzero(e->data, e->size_line * 990);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y);
	draw_point(e);
	return (1);
}
