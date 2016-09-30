/* ********************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 18:52:37 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/30 04:03:08 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

/*
**	void	draw_point_old(t_env *e);
**	void	main_work(t_env *e);
*/


void	loop_hook_brgin(t_env *e)
{
	static	double	increm = 0.03;

	(e->key.rot_z2 == 1) ? e->rot_z -= increm : (void)e;
	(e->key.rot_y2 == 1) ? e->rot_y -= increm : (void)e;
	(e->key.rot_x2 == 1) ? e->rot_x -= increm : (void)e;
	(e->key.rot_x1 == 1) ? e->rot_x += increm : (void)e;
	(e->key.rot_y1 == 1) ? e->rot_y += increm : (void)e;
	(e->key.rot_z1 == 1) ? e->rot_z += increm : (void)e;
	manage_cam_rot(e);
	(e->key.echap == 1) ? ft_exit(&e) : (void)e->key.echap;
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
}

int		loop_hook(t_env *e)
{
	double	incr;

	incr = 0.003;
	loop_hook_brgin(e);
	(e->key.fi1 == 1) ? e->dr1 += 5 *incr: (void)e;
	(e->key.fi_1 == 1) ? e->dr1 -= 5 * incr: (void)e;
	(e->key.fi2 == 1) ? e->dr2 += 15 * incr: (void)e;
	(e->key.fi_2 == 1) ? e->dr2 -= 15 * incr: (void)e;
	(e->key.isometric == 1) ? e->proj = 0 : (void)e->key.echap;
	(e->key.parallel == 1) ? e->proj = 1 : (void)e->key.echap;
	(e->key.conic == 1) ? e->proj = 2 : (void)e->key.echap;
	(e->key.r == 1) ? e->r += 20 : (void)e->key.echap;
	(e->key.g == 1) ? e->g += 20 : (void)e->key.echap;
	(e->key.b == 1) ? e->b += 20 : (void)e->key.echap;
	(e->key.speed_up == 1) ? e->speed += 1 : (void)e;
	(e->key.speed_down == 1) ? e->speed -= 1 : (void)e;
	(e->key.speed_stop == 1) ? e->speed = 0 : (void)e;
	e->view += (e->key.view == 1 && e->view_sw == 0) ? e->view_sw = 1 : 0;
	e->view_sw = (e->key.view == 0 && e->view_sw == 1) ? 0 : e->view_sw;
	e->draw += (e->key.draw == 1 && e->draw_sw == 0) ? e->draw_sw = 1 : 0;
	e->draw_sw = (e->key.draw == 0 && e->draw_sw == 1) ? 0 : e->draw_sw;
	increm_pos_cam(e);
	ft_bzero(e->data, e->size_line * e->ecr_y);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y * sizeof(double));
	main_work(e);
	return (1);
}
