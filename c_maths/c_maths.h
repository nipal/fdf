/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_maths.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/15 14:35:08 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/24 03:20:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_MATHS_H
# define C_MATHS_H

//#ifndef ABS
//#define ABS(X) ((X >= 0) ? X : -X)
//#endif

# include "libft.h"
# include <math.h>
# include <stdio.h>
//# include "../includes/fdf.h"
# define TRIGO_FACT	3
# define TRIGO_ACCURACY (TRIGO_FACT * 360)

//*
# define MIN(A, B) ((A) < (B) ? (A) : (B))
# define MAX(A, B) ((A) < (B) ? (B) : (A))
//*/
typedef struct	s_matrix
{
	double		*m;
	int			x;
	int			y;
}				t_matrix;

typedef struct	s_roots
{
	double		x1;
	double		x2;
	double		x3;
	double		x4;
	int			is_real;
}				t_roots;

typedef struct	s_coefs
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
}				t_coefs;

typedef	struct	s_eq
{
	t_matrix	*coef;
	t_matrix	*roots;
	int			nb_roots;
	int			dim;
	struct s_eq	*derivate;
	struct s_eq	*prime;
}				t_eq;

//void			print_repaire(t_matrix *min, t_matrix *pos, t_matrix *color, t_env *e)
void			eq_print(t_eq *eq);
void			eq_print_coef(t_eq *eq);
void			eq_print_roots(t_eq *eq);
void			eq_print_all_deriv(t_eq *eq);


t_eq			*eq_init(int dim, t_matrix *coef);
t_eq			*eq_creat(int dim);
t_eq			*eq_derivation(t_eq *eq);

int				eq_solve(t_eq *eq);
int				eq_solve_deg1(t_eq *eq);
int				eq_solve_deg2(t_eq *eq);
int				eq_solve_deg3(t_eq *eq);
int				eq_solve_deg4(t_eq *eq);
int				eq_solve_degn(t_eq *eq, int accuracy);


t_matrix		*matrix_init(int x, int y);
void			matrix_display(t_matrix *a);
t_matrix		*matrix_add(t_matrix *a, t_matrix *b);
t_matrix		*matrix_add_in(t_matrix *a, t_matrix *b, t_matrix *c);
t_matrix		*matrix_sub(t_matrix *a, t_matrix *b);
void			matrix_sub_in(t_matrix *a, t_matrix *b, t_matrix *c);
t_matrix		*matrix_product(t_matrix *a, t_matrix *b);
void			matrix_product_in(t_matrix *a, t_matrix *b, t_matrix *c);
void			vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result);
t_matrix		*matrix_scalar_product(t_matrix *a, double d);
t_matrix		*matrix_scalar_product_new(t_matrix *a, double d);
double			matrix_det(t_matrix *a);
t_matrix		*matrix_transpose(t_matrix *a, t_matrix *b);
double			matrix_norme(t_matrix *a);
t_matrix		*vector_product(t_matrix *a, t_matrix *b);
t_matrix		*vector_product_s(t_matrix *a, t_matrix *b, int x, int y);
void			vector_product_in(t_matrix *a, t_matrix *b, t_matrix *result);
double			matrix_dot_product(t_matrix *a, t_matrix *b);

t_matrix		*matrix_copy(t_matrix *src);
int				free_matrix(t_matrix *mat);
int				matrix_free(t_matrix **mat);

double			ft_cos(double deg);
double			ft_sin(double deg);

t_roots			eq_solve_2nd(t_coefs coefs);
t_roots			eq_solve_3rd(t_coefs coefs);
t_roots			eq_solve_4th(t_coefs coefs);

t_matrix		*matrix_buffer(t_matrix *mat);
void			matrix_put_in(double a, double b, double c, double d);
t_matrix		*matrix_put_in_new(double a, double b, double c, double d);

t_matrix		*set_rotate(double thetx, double thety, double thetz);
t_matrix		*set_translate(double dx, double dy, double dz);
t_matrix		*set_scale(double sx, double sy, double sz);

void	print_line(t_matrix *pt1, t_matrix *c1,  t_matrix *pt2, t_matrix *c2);

#endif
