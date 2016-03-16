/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/16 04:48:06 by fjanoty          ###   ########.fr       */
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
	key->speed_down = 0;
	key->speed_up = 0;
}

int		key_press(int keycode, t_env *e)
{
	(keycode == 27) ? e->key.speed_down = 1 :  0;
	(keycode == 24) ? e->key.speed_up = 1 :  0;
	(keycode == 0) ? e->key.rot_z2 = 1 :  0;
	(keycode == 1) ? e->key.rot_x1 = 1 :  0;
	(keycode == 2) ? e->key.rot_z1 = 1 :  0;
	(keycode == 12) ? e->key.rot_y2 = 1 :  0;
	(keycode == 13) ? e->key.rot_x2 = 1 :  0;
	(keycode == 14) ? e->key.rot_y1 = 1 :  0;
	(keycode == 53) ? e->key.echap = 1 :  0;
	(keycode == 53) ? e->key.echap = 1 :  0;
	(keycode == 125) ? e->key.decal_down = 1 :  0;
	(keycode == 126) ? e->key.decal_up = 1 :  0;
	(keycode == 124) ? e->key.decal_right = 1 :  0;
	(keycode == 123) ? e->key.decal_left = 1 :  0;
	(keycode == 69) ? e->key.zoom = 1 :  0;
	(keycode == 78) ? e->key.zoom_back = 1 :  0;
	(keycode == 24) ? e->key.scale_increase = 1 :  0;
	(keycode == 27) ? e->key.scale_decrease = 1 :  0;
	(keycode == 2) ? e->key.cte1_increase = 1 :  0;
	(keycode == 0) ? e->key.cte1_decrease = 1 :  0;
	(keycode == 34) ? e->key.isometric = 1 :  0;
	(keycode == 35) ? e->key.parallel = 1 :  0;
	(keycode == 8) ? e->key.conic = 1 :  0;
	(keycode == 15) ? e->key.r = 1 :  0;
	(keycode == 5) ? e->key.g = 1 :  0;
	(keycode == 11) ? e->key.b = 1 :  0;
	return (1);
}

int		key_release(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	(keycode == 27) ? e->key.speed_down = 0 :  0;
	(keycode == 24) ? e->key.speed_up = 0 :  0;
	(keycode == 0) ? e->key.rot_z2 = 0 :  0;
	(keycode == 1) ? e->key.rot_x1 = 0 :  0;
	(keycode == 2) ? e->key.rot_z1 = 0 :  0;
	(keycode == 12) ? e->key.rot_y2 = 0 :  0;
	(keycode == 13) ? e->key.rot_x2 = 0 :  0;
	(keycode == 14) ? e->key.rot_y1 = 0 :  0;
	(keycode == 53) ? e->key.echap = 0 :  0;
	(keycode == 125) ? e->key.decal_down = 0 :  0;
	(keycode == 126) ? e->key.decal_up = 0 :  0;
	(keycode == 124) ? e->key.decal_right = 0 :  0;
	(keycode == 123) ? e->key.decal_left = 0 :  0;
	(keycode == 69) ? e->key.zoom = 0 :  0;
	(keycode == 78) ? e->key.zoom_back = 0 :  0;
	(keycode == 24) ? e->key.scale_increase = 0 :  0;
	(keycode == 27) ? e->key.scale_decrease = 0 :  0;
	(keycode == 2) ? e->key.cte1_increase = 0 :  0;
	(keycode == 0) ? e->key.cte1_decrease = 0 :  0;
	(keycode == 34) ? e->key.isometric = 0 :  0;
	(keycode == 35) ? e->key.parallel = 0 :  0;
	(keycode == 8) ? e->key.conic = 0 :  0;
	(keycode == 15) ? e->key.r = 0 :  0;
	(keycode == 5) ? e->key.g = 0 :  0;
	(keycode == 11) ? e->key.b = 0 :  0;
	return (1);
}

int		incr_pos(t_env *e, t_cam *cam, t_matrix *ang)
{
	t_matrix	*rot;
	t_matrix	*dir;

	rot = NULL;
	if (!(rot = set_rotate(ang->m[X], ang->m[Y], ang->m[Z]))
		|| !(dir = matrix_product(rot, cam->dir)))
		{dprintf(1, "FAILE ICREM POS");return (0);}
	matrix_scalar_product(dir, 0.1 * e->speed);
	cam->pos->m[X] += dir->m[X];
	cam->pos->m[Y] += dir->m[Y];
	cam->pos->m[Z] += dir->m[Z];
	matrix_free(&rot);
	matrix_free(&dir);
	return (1);
}

int		loop_hook(t_env *e)
{
	double	increm;
	
	increm = 0.03;
//	dprintf(1, "x:%f y:%f x:%f\n", e->rot_x, e->rot_y, e->rot_z);
	(e->key.speed_up == 1) ? e->speed += 1: 0;
	(e->key.speed_down == 1) ? e->speed -= 1: 0;
	(e->key.rot_z2 == 1) ? e->cam->rot->m[Z] -= increm : 0;
	(e->key.rot_x2 == 1) ? e->cam->rot->m[X] -= increm : 0;
	(e->key.rot_z1 == 1) ? e->cam->rot->m[Z] += increm : 0;
	(e->key.rot_y2 == 1) ? e->cam->rot->m[Y] -= increm : 0;
	(e->key.rot_x1 == 1) ? e->cam->rot->m[X] += increm : 0;
	(e->key.rot_y1 == 1) ? e->cam->rot->m[Y] += increm : 0;
	(e->key.echap == 1) ? exit(0) : (void)e->key.echap;
	(e->key.decal_down == 1) ? e->decaly -= e->zoom / 2 : 0;
	(e->key.decal_up == 1) ? e->decaly += e->zoom / 2 : 0;
	(e->key.decal_right == 1) ? e->decalx -= e->zoom / 2 : 0;
	(e->key.decal_left == 1) ? e->decalx += e->zoom / 2 : 0;
	(e->key.zoom == 1) ? e->zoom += 4 : 0;
	(e->key.zoom_back == 1) ? e->zoom -= 4 : 0;
	(e->key.scale_increase == 1) ? e->scale += 0.2 : 0;
	(e->key.scale_decrease == 1) ? e->scale -= 0.2 : 0;
	(e->key.cte1_increase == 1) ? e->cte1 += 0.01 : 0;
	(e->key.cte1_decrease == 1) ? e->cte1 -= 0.01 : 0;
	(e->key.isometric == 1) ? e->proj = 0 : 0;
	(e->key.parallel == 1) ? e->proj = 1 : 0;
	(e->key.conic == 1) ? e->proj = 2 : 0;
	(e->key.r == 1) ? e->r += 20 : 0;
	(e->key.g == 1) ? e->g += 20 : 0;
	(e->key.b == 1) ? e->b += 20 : 0;
	ft_bzero(e->data, e->size_line * 990);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y);
	draw_point(e);
	incr_pos(e, e->cam, e->cam->rot); 
	return (1);
}
