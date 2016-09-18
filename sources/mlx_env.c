/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/18 07:48:42 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

void	px_to_img(t_env *e, int x, int y, int color)
{
//	(void)color;
//	printf("color:%0x\n", color);
//	printf("	r:%0x\n", (color & 0x00FF0000) >> 16);
//	printf("	v:%0x\n", (color & 0x0000FF00) >> 8);
//	printf("	b:%0x\n", (color & 0x000000FF) );
	y = 100;
	e->data[y * e->size_line + x * 4 + 2] = (color & 0x00FF0000) >> 16;
	e->data[y * e->size_line + x * 4 + 1] = (color & 0x0000FF00) >> 8;
	e->data[y * e->size_line + x * 4] = (color & 0x000000FF);
//	dprintf(1, "x:%d y:%d  color:%d\n", x, y, color);
}

void	vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int) pos_color->m[0];
	y = (int) pos_color->m[1];
	x += SIZE_Y / 2;
	y += SIZE_X / 2;
	if ( x < 0 || x >= e->size_line / 4 || y < 0 || y >= 990)
	{
//		dprintf(1, "x_max:%d y_max:%d\n", e->size_line  / 4, 990);
//		dprintf(1, "out of window x:%d y:%d\n", x, y);
		return ;
	}
	r = (int) pos_color->m[3] + 0.5;
	g = (int) pos_color->m[4] + 0.5;
	b = (int) pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
//	dprintf(1, "======= YEAHHHH BABY  ====== x:%d y:%d  r:%d v:%d b:%d ilne:%d\n", x, y, r, g, b, e->size_line);
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

	string_put("Zoom : ", ft_itoa(e->zoom), e, 50);
	(e->proj == 0) ? str = ft_strdup("isometric") : (void)e->proj;
	(e->proj == 1) ? str = ft_strdup("parallel") : (void)e->proj;
	(e->proj == 2) ? str = ft_strdup("conic") : (void)e->proj;
	string_put("Projection : ", str, e, 60);
	ft_strdel(&str);
	string_put("Offset X : ", ft_itoa(e->decalx), e, 70);
	string_put("Offset Y : ", ft_itoa(e->decaly), e, 80);
	str = ft_strnew(20);
	str = ft_strcat(str, " R = ");
	str = ft_strcat(str, ft_itoa((int)e->r));
	str = ft_strcat(str, " G = ");
	str = ft_strcat(str, ft_itoa((int)e->g));
	str = ft_strcat(str, " B = ");
	str = ft_strcat(str, ft_itoa((int)e->b));
	string_put(str, "", e, 90);
	ft_strdel(&str);
}

/*	ici il faudrait stoquer les dimetion maximale de la map
 * 	on a deja le max x et y il maque le max et le min en z*/

t_matrix	*get_max_zdim(int **map, int size_x, int size_y)
{
	int			i;
	int			j;
	t_matrix	*z_dim;

	if (!(z_dim = matrix_init(2, 1)))
		return (NULL);
	z_dim->m[0] = map[0][0];	
	z_dim->m[1] = map[0][0];	
	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			if (map[j][i] < z_dim->m[0])
				z_dim->m[0] = map[j][i];
			if (map[j][i] > z_dim->m[1])
				z_dim->m[1] = map[j][i];
			i++;
		}
		j++;
	}
	return (z_dim);
}

void	env(int **map, int size_x, int size_y)
{
	(void)size_x;
	(void)size_y;
	t_env	e;
	t_cam	*cam;
	t_matrix	*z_dim;

	if (!(z_dim = get_max_zdim(map, size_x, size_y)))
		return ;
	e.z_min = z_dim->m[0];
	e.z_max = z_dim->m[1];
	e.rot_x = (20.0 / 360.0)  * 2 * M_PI;
	e.rot_y = (20.0 / 360.0) * 2 * M_PI;
	e.rot_z = (0.0 / 360.0) * 2 * M_PI;
	e.size_map_x = size_x;	
	e.size_map_y = size_y;	
	e.map = map;
	e.vect_map = get_map(&e);
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_Y, SIZE_X, "Leu test");
	e.img = mlx_new_image(e.mlx, SIZE_Y, SIZE_X);
	e.data = mlx_get_data_addr(e.img, &e.depth, &e.size_line, &e.endian);
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	e.ecr_x = SIZE_Y;
	e.ecr_y = SIZE_X;
	e.proj = 0;
	e.scale = 2.5;
	e.cte1 = 0.6;
	e.zoom = 8;
	e.decalx = 150;
	e.decaly = 150;
	e.r = 255;
	e.g = 0;
	e.b = 0;
	e.speed = 0;
//	dprintf(1, "ouiii\n");
	if (!(cam = init_cam(60.0/360.0 * M_PI , 60.0/360.0 * M_PI, &e)))
		return ;
	e.cam = cam;
	dprintf(1, "ouiii\n");
	init_t_key(&e.key);
	mlx_hook(e.win, 2, 1, key_press, &e);
	mlx_hook(e.win, 3, 2, key_release, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	free(z_dim);
}
