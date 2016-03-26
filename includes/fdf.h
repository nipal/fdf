/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/29 02:21:11 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/26 21:56:13 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "c_maths.h"

/*
 **	mat_line
 **/
# define SIZE_BUFF 256

# define COEF 2
# define SIZE 3

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


# define BEG_POS 0
# define DELTA_POS 1
# define BEG_COL 2
# define DELTA_COL 3

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
	int					rot_x1;
	int					rot_y1;
	int					rot_z1;
	int					rot_x2;
	int					rot_y2;
	int					rot_z2;
	int					speed_up;
	int					speed_down;
}						t_key;


//*
# define TOP_LEFT 0
# define BOTOM_LEFT 1
# define BOTOM_RIGHT 2
# define TOP_RIGHT 3
//# define MM 4

# define LEFT 0 
# define BOTOM 1
# define RIGHT 2
# define TOP 3
typedef	struct			s_cam
{
	t_matrix			**corner;
	t_matrix			**normal;
	t_matrix			*pos;
	t_matrix			*dir;
	t_matrix			*rot;
	t_matrix			**repere;
}						t_cam;
//*/

/*
 **	on a un repe cam_x, cam_y, cam_z, cam_origin
 **	x = dot_product(diff , cam_x);
 **	y = dot_product(diff , cam_y);
 **	z = dot_product(diff , cam_z);
 **	
 * */

# define SIZE_X 1440
# define SIZE_Y 990
# define PRINT_DIAG 0
typedef struct			s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	double				*z_buffer;
	int					size_line;
	int					ecr_x;
	int					ecr_y;
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
	int					map_x;
	int					map_y;
	double				max_z;
	double				min_z;
	double				rot_x;
	double				rot_y;
	double				rot_z;
	double				speed;
	t_cam				*cam;
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
void					vectpx_to_img(t_env *e, t_matrix *pos_color);
void					pix_to_img(t_env *e, t_matrix *pos, t_matrix *color);
void					print_state(t_env *e);

//	Fonction preparant l'env et qui lance le loop hook
void					env(int fd);
/*
** coord
*/

/*
 **	cam
 **/
t_cam	*init_cam(double fov_y, double fov_x, t_env *e);
/*
 ** print_map	
 * */
void	print_map(t_env *e, t_cam *cam, t_matrix ***map);

/*
** draw
*/
//fonctions de dessin (putline, put map of vect)
void					draw_point(t_env *e);
/*
** parsing
**	int						**parse(int fd);
*/

//int						**parse(int fd);
t_list	*get_file(int fd);
char	*get_str(t_list *lst);
int		get_tabsize(char **tab);
int		free_chartab(char **tab);
int		*fill_line(char **char_line, int size_line);
int		**get_number(char *str, int *size_line, int *nb_line);
void		define_color(t_env *e, t_matrix*** map, int nbl, int min);
t_matrix	***get_matrix_map(t_env *e);



t_matrix	***get_map(t_env *e, double *z_max, double *z_min);
void	draw_line(t_env *e, t_matrix *mat_line);
t_matrix	*init_mat_line(t_matrix *pt1, t_matrix *pt2, t_matrix *c1, t_matrix *c2);
void	print_line(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2);
void	line_x(t_env *e, t_matrix *eq, t_matrix *c1, t_matrix *diff_c);
void	line_y(t_env *e, t_matrix *eq, t_matrix *c1, t_matrix *diff_c);
t_matrix	**tab_matrix(t_matrix *pt1, t_matrix *pt2, t_matrix *pt3);
#endif
