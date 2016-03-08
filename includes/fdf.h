/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/08 03:43:20 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "c_maths.h"

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

# define BEG_X 0
# define END_X 1
# define DELTA_Y 2
# define BEG_Y 3
# define MAX_Y 4
# define MIN_Y 5

# define X 0
# define Y1 1
# define Y2 2

# define BEG_Z 0
# define DELTA_Z 1

# define X1 0
# define Y1 1
# define Z1 2
# define DX 3
# define DY 4
# define DZ 5
# define R1 6
# define G1 7
# define B1 8
# define DR 9
# define DG 10
# define DB 11
# define NORME 12

typedef struct			s_key
{
	int					echap;
	int					decal_down;
	int					decal_up;
	int					decal_right;
	int					decal_left;
	int					zoom;
	int					zoom_back;
	int					cte1_increase;
	int					cte1_decrease;
	int					isometric;
	int					parallel;
	int					conic;
	int					scale_increase;
	int					scale_decrease;
	int					r;
	int					g;
	int					b;
}						t_key;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					size_line;
	int					depth;
	int					endian;
	int					**map;
	int					proj;
	double				scale;
	double				cte1;
	int					decalx;
	int					decaly;
	int					zoom;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
	t_key				key;
}						t_env;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	unsigned int		color;
}						t_point;

/*
** hook
*/
void					init_t_key(t_key *key);
int						key_press(int keycode, t_env *e);
int						key_release(int keycode, t_env *e);

//	redessine et set les vars en fonction des inputs
int						loop_hook(t_env *e);

/*
** mlx_env
*/
void					px_to_img(t_env *e, int x, int y, int color);
void					print_state(t_env *e);

//	Fonction preparant l'env et qui lance le loop hook
void					env(int **map);
/*
** coord
*/


/*
** draw
*/
//fonctions de dessin (putline, put map of vect)
void					draw_point(t_env *e);
/*
** parse
*/
int						**parse(int fd);

#endif
