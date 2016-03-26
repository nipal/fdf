/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/24 20:32:59 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

void	px_to_img(t_env *e, int x, int y, int color)
{
	;//dprintf(2, "\n\n\n\n\n\n*********************************1\n");
//	(void)color;
//	printf("color:%0x\n", color);
//	printf("	r:%0x\n", (color & 0x00FF0000) >> 16);
//	printf("	v:%0x\n", (color & 0x0000FF00) >> 8);
//	printf("	b:%0x\n", (color & 0x000000FF) );
	y = 100;
	e->data[y * e->size_line + x * 4 + 2] = (color & 0x00FF0000) >> 16;
	e->data[y * e->size_line + x * 4 + 1] = (color & 0x0000FF00) >> 8;
	e->data[y * e->size_line + x * 4] = (color & 0x000000FF);
//	;//dprintf(1, "x:%d y:%d  color:%d\n", x, y, color);
}

/*
void	vectpx_to_img2(t_env *e, t_matrix *pos, t_matrix *color)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int) pos_color->m[0];
	y = (int) pos_color->m[1];
	if ( x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y)
	{
//		;//dprintf(1, "x_max:%d y_max:%d\n", e->size_line  / 4, 990);
//		;//dprintf(1, "out of window x:%d y:%d\n", x, y);
		return ;
	}
	r = (int) pos_color->m[3] + 0.5;
	g = (int) pos_color->m[4] + 0.5;
	b = (int) pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
//	;//dprintf(1, "======= YEAHHHH BABY  ====== x:%d y:%d  r:%d v:%d b:%d ilne:%d\n", x, y, r, g, b, e->size_line);
}
*/


void	pix_to_img(t_env *e, t_matrix *pos, t_matrix *color)
{
	int	x;
	int	y;

	x = (int) pos->m[X];
	y = (int) pos->m[Y];
//	dprintf(1, "x:%d	y:%d\n", x, y);
	if ( x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y)
	{
		return ;
	}
	e->data[y * e->size_line + x * 4 + 2] = (int)color->m[R];
	e->data[y * e->size_line + x * 4 + 1] = (int)color->m[G];
	e->data[y * e->size_line + x * 4] = (int)color->m[B];
}

void	vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	;//dprintf(2, "\n\n\n\n\n\n*********************************3\n");
//	sleep(10);
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int) pos_color->m[0];
	y = (int) pos_color->m[1];
	if ( x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y)
	{
//		;//dprintf(1, "x_max:%d y_max:%d\n", e->size_line  / 4, 990);
//		;//dprintf(1, "out of window x:%d y:%d\n", x, y);
		return ;
	}
	r = (int) pos_color->m[3] + 0.5;
	g = (int) pos_color->m[4] + 0.5;
	b = (int) pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
//	;//dprintf(1, "======= YEAHHHH BABY  ====== x:%d y:%d  r:%d v:%d b:%d ilne:%d\n", x, y, r, g, b, e->size_line);
}

void	string_put(char *s1, char *s2, t_env *e, int y)
{
	char *str;

	str = ft_strnew(60);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	mlx_string_put(e->mlx, e->win, 1200, y, 0xFFFF00, str);
}

void	print_state(t_env *e)
{
	char	*str;

	string_put("speed : ", ft_itoa(e->speed), e, 50);
	string_put("rot_x : ", ft_itoa(e->cam->rot->m[X]), e, 70);
	string_put("rot_y : ", ft_itoa(e->cam->rot->m[Y]), e, 90);
	string_put("rot_z : ", ft_itoa(e->cam->rot->m[Z]), e, 110);
	/*
	(e->proj == 0) ? str = ft_strdup("isometric") : (void)e->proj;
	(e->proj == 1) ? str = ft_strdup("parallel") : (void)e->proj;
	(e->proj == 2) ? str = ft_strdup("conic") : (void)e->proj;
	*/
//	string_put("Projection : ", str, e, 60);
//	ft_strdel(&str);
	string_put("Offset X : ", ft_itoa(e->decalx), e, 130);
	string_put("Offset Y : ", ft_itoa(e->decaly), e, 150);
	str = ft_strnew(20);
	str = ft_strcat(str, " R = ");
	str = ft_strcat(str, ft_itoa((int)e->r));
	str = ft_strcat(str, " G = ");
	str = ft_strcat(str, ft_itoa((int)e->g));
	str = ft_strcat(str, " B = ");
	str = ft_strcat(str, ft_itoa((int)e->b));
	string_put(str, "", e, 170);
	ft_strdel(&str);
}

void	env(int **map)
{
	t_env	e;

	e.map = map;
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_X, SIZE_Y, "sandwich");
	e.img = mlx_new_image(e.mlx, SIZE_X, SIZE_Y);
	e.data = mlx_get_data_addr(e.img, &e.depth, &e.size_line, &e.endian);
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	e.size_map_x = 11;	
	e.size_map_y = 19;	
	e.ecr_x = SIZE_X;
	e.ecr_y = SIZE_Y;
	e.proj = 0;
	e.scale = 2.5;
	e.cte1 = 0.6;
	e.zoom = 8;
	e.decalx = 150;
	e.decaly = 150;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	e.rot_x = 0;
	e.rot_y = 0;
	e.rot_z = 0;
	e.speed = 0;
	e.cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 *M_PI, &e);
	init_t_key(&e.key);
	line_x(&e, 0, 0, 0);
	line_y(&e, 0, 0, 0);
	mlx_hook(e.win, 2, 1, key_press, &e);
	mlx_hook(e.win, 3, 2, key_release, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
}
