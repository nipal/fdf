/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:52:17 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/23 06:58:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

void	init_t_key_2(t_key *key)
{
	key->rot_z1 = 0;
	key->rot_z2 = 0;
	key->rot_x1 = 0;
	key->rot_x2 = 0;
	key->rot_y1 = 0;
	key->rot_y2 = 0;
	key->rot_cam_z1 = 0;
	key->rot_cam_z2 = 0;
	key->rot_cam_x1 = 0;
	key->rot_cam_x2 = 0;
	key->rot_cam_y1 = 0;
	key->rot_cam_y2 = 0;
	key->speed_up = 0;
	key->speed_down = 0;
	key->speed_stop = 0;
	key->fi1 = 0;
	key->fi_1 = 0;
	key->fi2 = 0;
	key->fi_2 = 0;
	key->view = 0;
	key->z_up = 0;
	key->z_down = 0;
}

void	init_t_key(t_key *key)
{
	key->echap = 0;
	key->decal_down = 0;
	key->decal_up = 0;
	key->decal_right = 0;
	key->decal_left = 0;
	key->cte1_increase = 0;
	key->cte1_decrease = 0;
	key->scale_increase = 0;
	key->scale_decrease = 0;
	key->r = 0;
	key->g = 0;
	key->b = 0;
	key->draw = 0;
	init_t_key_2(key);
}

void	key_press_end(int keycode, t_env *e)
{
	(keycode == 18) ? e->key.z_up = 1 : (void)keycode;
	(keycode == 19) ? e->key.z_down = 1 : (void)keycode;
	(keycode == 53) ? e->key.echap = 1 : (void)keycode;
	(keycode == 125) ? e->key.decal_down = 1 : (void)keycode;
	(keycode == 126) ? e->key.decal_up = 1 : (void)keycode;
	(keycode == 124) ? e->key.decal_right = 1 : (void)keycode;
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
	(keycode == 15) ? e->key.r = 1 : (void)keycode;
	(keycode == 5) ? e->key.g = 1 : (void)keycode;
	(keycode == 11) ? e->key.b = 1 : (void)keycode;
}

int		key_press(int keycode, t_env *e)
{
	(keycode == 36) ? e->key.switch_anime = 1 : (void)keycode;
	(keycode == 45) ? e->key.view = 1 : (void)keycode;
	(keycode == 46) ? e->key.draw = 1 : (void)keycode;
	(keycode == 6) ? e->key.fi1 = 1 : (void)keycode;
	(keycode == 7) ? e->key.fi_1 = 1 : (void)keycode;
	(keycode == 8) ? e->key.fi2 = 1 : (void)keycode;
	(keycode == 9) ? e->key.fi_2 = 1 : (void)keycode;
	(keycode == 27) ? e->key.speed_down = 1 : (void)keycode;
	(keycode == 24) ? e->key.speed_up = 1 : (void)keycode;
	(keycode == 29) ? e->key.speed_stop = 1 : (void)keycode;
	(keycode == 13) ? e->key.rot_x1 = 1 : (void)keycode;
	(keycode == 12) ? e->key.rot_y1 = 1 : (void)keycode;
	(keycode == 0) ? e->key.rot_z1 = 1 : (void)keycode;
	(keycode == 1) ? e->key.rot_x2 = 1 : (void)keycode;
	(keycode == 14) ? e->key.rot_y2 = 1 : (void)keycode;
	(keycode == 2) ? e->key.rot_z2 = 1 : (void)keycode;
	(keycode == 32) ? e->key.rot_cam_x1 = 1 : (void)keycode;
	(keycode == 34) ? e->key.rot_cam_y1 = 1 : (void)keycode;
	(keycode == 38) ? e->key.rot_cam_z1 = 1 : (void)keycode;
	(keycode == 31) ? e->key.rot_cam_x2 = 1 : (void)keycode;
	(keycode == 40) ? e->key.rot_cam_y2 = 1 : (void)keycode;
	(keycode == 37) ? e->key.rot_cam_z2 = 1 : (void)keycode;
	key_press_end(keycode, e);
	return (1);
}
