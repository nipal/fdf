/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 01:26:10 by fjanoty           #+#    #+#             */
/*   Updated: 2016/10/23 10:32:16 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

/*
**	void	draw_point_old(t_env *e);
**	void	main_work(t_env *e);
*/

void	loop_hook_begin(t_env *e)
{
	static	double	increm = 0.06;

	(e->key.z_down == 1) ? e->mult_z -= 0.2 : (void)e;
	(e->key.z_up == 1) ? e->mult_z += 0.2 : (void)e;
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

void	actu_anime_torus(t_env *e)
{
	int			yolo_compile;
	static	int		sap = 1;
	static	double	a = 0.00000015;

	yolo_compile = 0;
	if (e->key.switch_anime == 0)
		sap = 0;
	else if (e->key.switch_anime == 1 && sap == 0 && (e->increm *= -1)
		&& (sap = 1))
		yolo_compile = 0;
	e->view += (e->key.view == 1 && e->view_sw == 0) ? e->view_sw = 1 : 0;
	e->view_sw = (e->key.view == 0 && e->view_sw == 1) ? 0 : e->view_sw;
	e->draw += (e->key.draw == 1 && e->draw_sw == 0) ? e->draw_sw = 1 : 0;
	e->draw_sw = (e->key.draw == 0 && e->draw_sw == 1) ? 0 : e->draw_sw;
	if ((e->increm < 0 && e->beta > M_PI / 4)
		|| (e->increm > 0 && e->beta < M_PI / 2))
		e->beta += e->increm;
	e->beta = (e->increm < 0 && BETA < M_PI / 4) ? M_PI / 4 - a : BETA;
	e->beta = (e->increm > 0 && BETA > M_PI / 2) ? M_PI / 2 + a : BETA;
	e->anime_advence = (1 - (2 * (e->beta / (0.5 * M_PI) - 0.5) - a));
	e->k = tan(e->beta);
	e->advence = (e->view % 2) ? (e->beta - (M_PI / 4)) / (M_PI / 4) : 1;
	e->phi1 = 2 * M_PI / e->k;
	e->phi2 = (e->view % 2 == 0) ? 2 * M_PI
		/ e->k : (M_PI * (1 + e->advence)) / e->k;
	sap += yolo_compile;
}

int		loop_hook(t_env *e)
{
	double		incr;

	incr = .003;
	loop_hook_begin(e);
	(e->key.fi1 == 1) ? e->dr1 += 10 * incr : (void)e;
	(e->key.fi_1 == 1) ? e->dr1 -= 10 * incr : (void)e;
	(e->key.fi2 == 1) ? e->dr2 += 20 * incr : (void)e;
	(e->key.fi_2 == 1) ? e->dr2 -= 20 * incr : (void)e;
	(e->key.r == 1) ? e->r += 20 : (void)e->key.echap;
	(e->key.g == 1) ? e->g += 20 : (void)e->key.echap;
	(e->key.b == 1) ? e->b += 20 : (void)e->key.echap;
	(e->key.speed_up == 1) ? e->speed = 6 : (void)e;
	(e->key.speed_down == 1) ? e->speed = -6 : (void)e;
	(e->key.speed_stop == 1) ? e->speed = 0 : (void)e;
	actu_anime_torus(e);
	increm_pos_cam(e);
	ft_bzero(e->data, e->size_line * e->ecr_y);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y * sizeof(double));
	main_work(e);
	return (1);
}
