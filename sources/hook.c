/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 12:17:52 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/18 10:24:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"

void	draw_point_old(t_env *e);
void	main_work(t_env *e);

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
	key->rot_cam_z1 = 0;
	key->rot_cam_z2 = 0;
	key->rot_cam_x1 = 0;
	key->rot_cam_x2 = 0;
	key->rot_cam_y1 = 0;
	key->rot_cam_y2 = 0;
	key->speed_up = 0;
	key->speed_down = 0;
}

int		key_press_mac(int keycode, t_env *e)
{
	(keycode == 78) ? e->key.speed_down = 1 : (void)keycode;
	(keycode == 69) ? e->key.speed_up = 1 : (void)keycode;

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
	(keycode == 34) ? e->key.isometric = 1 : (void)keycode;
	(keycode == 35) ? e->key.parallel = 1 : (void)keycode;
	(keycode == 8) ? e->key.conic = 1 : (void)keycode;
	(keycode == 15) ? e->key.r = 1 : (void)keycode;
	(keycode == 5) ? e->key.g = 1 : (void)keycode;
	(keycode == 11) ? e->key.b = 1 : (void)keycode;
	return (1);
}

int		key_press(int keycode, t_env *e)
{
	(keycode == '-') ? e->key.speed_down = 1 : (void)keycode;
	(keycode == '=') ? e->key.speed_up = 1 : (void)keycode;

	(keycode == 'a') ? e->key.rot_x1 = 1 : (void)keycode;
	(keycode == 'w') ? e->key.rot_y1 = 1 : (void)keycode;
	(keycode == 'q') ? e->key.rot_z1 = 1 : (void)keycode;
	(keycode == 'd') ? e->key.rot_x2 = 1 : (void)keycode;
	(keycode == 's') ? e->key.rot_y2 = 1 : (void)keycode;
	(keycode == 'e') ? e->key.rot_z2 = 1 : (void)keycode;

	(keycode == 'k') ? e->key.rot_cam_x1 = 1 : (void)keycode;
	(keycode == 'j') ? e->key.rot_cam_y1 = 1 : (void)keycode;
	(keycode == 'u') ? e->key.rot_cam_z1 = 1 : (void)keycode;
	(keycode == 'i') ? e->key.rot_cam_x2 = 1 : (void)keycode;
	(keycode == 'l') ? e->key.rot_cam_y2 = 1 : (void)keycode;
	(keycode == 'o') ? e->key.rot_cam_z2 = 1 : (void)keycode;

	(keycode == '`') ? e->key.echap = 1 : (void)keycode;
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
//	ft_putchar('[');
//	ft_putnbr(keycode);
//	ft_putstr("] ");

	(keycode == '-') ? e->key.speed_down = 0 : (void)keycode;
	(keycode == '=') ? e->key.speed_up = 0 : (void)keycode;

	(keycode == 'a') ? e->key.rot_x1 = 0 : (void)keycode;
	(keycode == 'w') ? e->key.rot_y1 = 0 : (void)keycode;
	(keycode == 'q') ? e->key.rot_z1 = 0 : (void)keycode;
	(keycode == 'd') ? e->key.rot_x2 = 0 : (void)keycode;
	(keycode == 's') ? e->key.rot_y2 = 0 : (void)keycode;
	(keycode == 'e') ? e->key.rot_z2 = 0 : (void)keycode;

	(keycode == 'k') ? e->key.rot_cam_x1 = 0 : (void)keycode;
	(keycode == 'j') ? e->key.rot_cam_y1 = 0 : (void)keycode;
	(keycode == 'u') ? e->key.rot_cam_z1 = 0 : (void)keycode;
	(keycode == 'i') ? e->key.rot_cam_x2 = 0 : (void)keycode;
	(keycode == 'l') ? e->key.rot_cam_y2 = 0 : (void)keycode;
	(keycode == 'o') ? e->key.rot_cam_z2 = 0 : (void)keycode;


	(keycode == '`') ? e->key.echap = 0 : (void)keycode;
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
	t_matrix	*tmp;
	t_matrix	*rot;
	t_matrix	*dir;

	if(!(rot = set_rotate(e->rot_x, e->rot_y, e->rot_z))
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
	int			i;
	t_matrix	*tmp;
	t_matrix	*rot;
	t_matrix	*mat_rot;
	(void)tmp;
	static	double	deg = 0.03;

	if (!(rot = matrix_init(1, 3)))
		return ;
	if (e->key.rot_cam_z2)
		rot->m[2] -= deg;
	if (e->key.rot_cam_z1)
		rot->m[2] += deg;
	if (e->key.rot_cam_x2)
		rot->m[0] -= deg;
	if (e->key.rot_cam_x1)
		rot->m[0] += deg;
	if (e->key.rot_cam_y2)
		rot->m[1] -= deg;
	if (e->key.rot_cam_y1)
		rot->m[1] += deg;
	if (!(mat_rot = set_rotate(rot->m[0], rot->m[1], rot->m[2])))
		return ;
	i = 0;
	while (i < 3)
	{
		if (!(tmp = matrix_product(mat_rot, e->cam->base[i])))
			return ;
		matrix_free(e->cam->base + i);
		e->cam->base[i] = tmp;
		i++;
	}
	matrix_free(&mat_rot);
	matrix_free(&rot);
}
//	si 
int		loop_hook(t_env *e)
{
	static	double	increm = 0.03;
	
//	dprintf(1, "x:%f y:%f x:%f\n", e->rot_x, e->rot_y, e->rot_z);
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
	(e->key.isometric == 1) ? e->proj = 0 : (void)e->key.echap;
	(e->key.parallel == 1) ? e->proj = 1 : (void)e->key.echap;
	(e->key.conic == 1) ? e->proj = 2 : (void)e->key.echap;
	(e->key.r == 1) ? e->r += 20 : (void)e->key.echap;
	(e->key.g == 1) ? e->g += 20 : (void)e->key.echap;
	(e->key.b == 1) ? e->b += 20 : (void)e->key.echap;
	(e->key.speed_up == 1) ? e->speed += 1 : (void)e;
	(e->key.speed_down == 1) ? e->speed -= 1 : (void)e;
	increm_pos_cam(e);
//	dprintf(1, "speed%f\n", e->speed);
	ft_bzero(e->data, e->size_line * e->ecr_y);
	ft_bzero(e->z_buffer, SIZE_X * SIZE_Y * sizeof(double));
//	main_work(e);
//	dprintf(1, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	avannnnnnnnnnt\n");
//	main_work(e);
ft_putstr("a1\n");
draw_point_old(e);
ft_putstr("a2\n");
//	dprintf(1, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	apreeeeeeeeeees\n");
//	draw_point(e);
//	draw_point_old(e);
	return (1);
}
