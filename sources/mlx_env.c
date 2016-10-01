/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 04:08:06 by jpirsch           #+#    #+#             */
/*   Updated: 2016/10/01 12:45:23 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fdf.h"
#include <stdio.h>

void	px_to_img(t_env *e, int x, int y, int color)
{
	y = 100;
	e->data[y * e->size_line + x * 4 + 2] = (color & 0x00FF0000) >> 16;
	e->data[y * e->size_line + x * 4 + 1] = (color & 0x0000FF00) >> 8;
	e->data[y * e->size_line + x * 4] = (color & 0x000000FF);
}
void	vectpx_to_img(t_env *e, t_matrix *pos_color)
{
	int	x;
	int	y;
	int	r;
	int	g;
	int	b;

	x = (int)pos_color->m[0];
	y = (int)pos_color->m[1];
	x += SIZE_Y / 2;
	y += SIZE_X / 2;
	if (x < 0 || x >= e->ecr_x || y < 0 || y >= e->ecr_y || pos_color->m[2] < 0
		|| (pos_color->m[2] >
			e->z_buffer[x + y * e->ecr_x] && e->z_buffer[x + y * e->ecr_x]))
		return ;
	e->z_buffer[x + y * e->ecr_x] = pos_color->m[2];
	r = (int)pos_color->m[3] + 0.5;
	g = (int)pos_color->m[4] + 0.5;
	b = (int)pos_color->m[5] + 0.5;
	e->data[y * e->size_line + x * 4 + 2] = r;
	e->data[y * e->size_line + x * 4 + 1] = g;
	e->data[y * e->size_line + x * 4] = b;
}

void	string_put(char *s1, char *s2, t_env *e, int y)
{
	char *str;

	str = ft_strnew(60);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	mlx_string_put(e->mlx, e->win, 1200, y, 0xFFFF00, str);
	free(str);
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

/*
** 	ici il faudrait stoquer les dimetion maximale de la map
** 	on a deja le max x et y il maque le max et le min en z
*/

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

t_matrix	*finishe_color(t_env *e, double *pak)
{
	t_matrix	*color;

	if (e->z_max != 0 && e->z_min < 0)
		pak[0] = 255 * pak[3] / e->z_max;
	else if (pak[2] != 0)
		pak[0] = 255 * pak[3] / pak[2];
	else
		pak[0] = 255;
	pak[1] = 255 - pak[0];
	if (!(color = vect_new_vertfd(pak[0], pak[1], 0)))
		return (NULL);
	return (color);
}

t_matrix	*set_color(t_env *e, double value)
{
	t_matrix	*color;
	double		pak[4];

	pak[3] = value;
	pak[2] = e->z_max - e->z_min;
	color = NULL;
	pak[0] = 0;
	if (pak[3] < 0)
	{
		if (e->z_max > 0)
			pak[0] = 255 * pak[3] / e->z_min;
		else if (pak[2] > 0)
			pak[0] = 255 * pak[3] / pak[2];
		else
			pak[0] = 255;
		pak[1] = 255 - pak[0];
		if (!(color = vect_new_vertfd(0, pak[1], pak[0])))
			return (NULL);
	}
	else
		color = finishe_color(e, pak);
	return (color);
}

int		map_color_init(t_env *e)
{
	t_matrix	***color;
	int			i;
	int			j;

	if (!(color = (t_matrix***)malloc(sizeof(t_matrix**) * e->size_map_y)))
		return (0);
	j = 0;
	while (j < e->size_map_y)
	{
		if (!(color[j] = (t_matrix**)malloc(sizeof(t_matrix*) * e->size_map_x)))
			return (0);
		i = 0;
		while (i < e->size_map_x)
		{
			if (!(color[j][i] = set_color(e, e->map[j][i])))
				return (0);
			i++;
		}
		j++;
	}
	e->color_map = color;
	return (1);
}

void	env_end(t_env *e)
{
	t_cam		*cam;

	e->dr1 = 0;
	e->dr2 = 0;
	e->ecr_x = SIZE_Y;
	e->ecr_y = SIZE_X;
	e->proj = 0;
	e->scale = 2.5;
	e->cte1 = 0.6;
	e->zoom = 8;
	e->decalx = 150;
	e->decaly = 150;
	e->r = 255;
	e->g = 0;
	e->b = 0;
	e->speed = 0;
	if (!(cam = init_cam(60.0 / 360.0 * M_PI, 60.0 / 360.0 * M_PI, e)))
		return ;
	e->cam = cam;
	init_t_key(&(e->key));
	mlx_hook(e->win, 2, 1, key_press, e);
	mlx_hook(e->win, 3, 2, key_release, e);
	mlx_loop_hook(e->mlx, loop_hook, e);
	mlx_loop(e->mlx);
}

void	env(int **map, int size_x, int size_y)
{
	t_env		e;
	t_matrix	*z_dim;

	if (!(z_dim = get_max_zdim(map, size_x, size_y)))
		return ;
	e.k = 1;
	e.phi1 = M_PI * 2;
	e.phi2 = M_PI * 2;
	e.beta = M_PI / 2 - 0.0001;
	e.nb_frame = 0.1 * MAX(size_x, size_y);
	e.increm = -(M_PI / (4 * e.nb_frame));
	e.view = 0;
	e.draw = 0;
	e.z_min = z_dim->m[0];
	e.z_max = z_dim->m[1];
	e.rot_x = (20.0 / 360.0) * 2 * M_PI;
	e.rot_y = (20.0 / 360.0) * 2 * M_PI;
	e.rot_z = (0.0 / 360.0) * 2 * M_PI;
	e.size_map_x = size_x;
	e.size_map_y = size_y;
	e.map = map;
	if (!(e.map_d = cast_tab(map, size_x, size_y)))
		return ;
	if (!(map_color_init(&e)))
		return ;
	if (!(e.mlx = mlx_init()))
		return ;
	e.win = mlx_new_window(e.mlx, SIZE_Y, SIZE_X, "Leu test");
	e.img = mlx_new_image(e.mlx, SIZE_Y, SIZE_X);
	e.data = mlx_get_data_addr(e.img, &(e.depth), &(e.size_line), &(e.endian));
	e.z_buffer = (double*)malloc(sizeof(double) * SIZE_X * SIZE_Y);
	env_end(&e);
	matrix_free(&z_dim);
}
