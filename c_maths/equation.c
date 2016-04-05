#include "c_maths.h"

t_eq			*eq_init(int dim, t_matrix *coef)
{
	t_eq	*eq;

	if (!(eq = (t_eq*)malloc(sizeof(t_eq))))
		return (NULL);
	eq->dim = dim;
	eq->coef = coef;
	eq->prime = NULL;
	eq->roots = NULL;
	eq->nb_roots = 0;
	eq->derivate = (dim > 0) ? eq_derivation(eq) : NULL;
	return (eq);
}

t_eq			*eq_creat(int dim)
{
	t_eq		*eq;
	t_matrix	*coef;

	if (!(eq = (t_eq*)malloc(sizeof(t_eq)))
		|| !(coef = matrix_init(1, dim + 1)))
		return (NULL);
	eq->dim = dim;
	eq->coef = coef;
	eq->prime = NULL;
	eq->roots = NULL;	
	eq->nb_roots = 0;
	eq->derivate = NULL;
	return (eq);
}

t_matrix		*eq_get_deriv_coef(t_eq *eq)
{
	t_matrix	*coef;
	int			i;

	if (!(coef = matrix_init(1, eq->dim)))
		return (NULL);
	i = 0;
	while (i < eq->dim)
	{
		coef->m[i] = (i + 1) * eq->coef->m[i + 1];
		i++;
	}
	return (coef);
}

t_eq			*eq_derivation(t_eq *eq)
{
	t_eq		*derivate;

	if (!(derivate = eq_init(eq->dim - 1, eq_get_deriv_coef(eq))) || eq->dim == 0)
		return (NULL);
	derivate->prime = eq;
	return (derivate);
}

void			eq_print_coef(t_eq *eq)
{
	int	i;

	i = eq->dim;
	while (i >= 0)
	{
		dprintf(1, "%f X^%d	", eq->coef->m[i], i);
		i--;
	}
	dprintf(1, "\n");
}

void			eq_print_all_deriv(t_eq *eq)
{
	t_eq	*deriv;
	int		i;

	dprintf(1, "f'{0}	:");
	eq_print_coef(eq);
	deriv = eq->derivate;
	i = 1;
	while (deriv)
	{
		dprintf(1, "f'{%d}	:", i);
		eq_print_coef(deriv);
		deriv = deriv->derivate;
		i++;
	}
}


void			eq_print_roots(t_eq *eq)
{
	int	i;

	i = 0;
	while (i < eq->nb_roots)
	{
		dprintf(1, "x[%d] = %f", i, eq->roots->m[i]);
		i++;
	}
	dprintf(1, "\n");
}

int				eq_solve(t_eq *eq)
{
	double	accuracy;

	accuracy = 30;
	if (eq->dim == 0)
		return(0);
	else if (eq->dim == 1)
		return (eq_solve_deg1(eq));
	else if (eq->dim == 2)
		return (eq_solve_deg2(eq));
	else
		return (eq_solve_degn(eq, accuracy));
}
int				eq_solve_deg1(t_eq *eq)
{
	double	a;
	double	b;

	a = eq->coef->m[1];
	b = eq->coef->m[0];
	if (a == 0)
		return (0);
	eq->nb_roots = 1;
	eq->roots->m[0] = -b / a;
	return (1);
}

int				eq_solve_deg2(t_eq *eq)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = eq->coef->m[2];
	b = eq->coef->m[1];
	c = eq->coef->m[0];
	if (a == 0 && b == 0)
		return (0);
	delta = b * b - 4 * a * c;
	delta = sqrt(delta);
	if (delta < 0)
		return (0);
	eq->nb_roots = 2;
	eq->roots->m[0] = (-b - delta) / (2 * a);
	eq->roots->m[1] = (-b + delta) / (2 * a);
	return (1);
}
int				eq_solve_degn(t_eq *eq, int accuracy)
{
	(void)eq;
	(void)accuracy;
	return (1);
}

/*
determiner les interval

si pas de racine on par de zero

premier:	-on part de la premier racine de la derive
				-si f(x0') * f'(x0') > 0 (mm signe)
					{premier racine est avant}
					-tan que (f(x) * f'(x) > 0)
						x = xo' - pow(2, i)
						i++
					begin = x
					end   = x0'

				-sinon
					begin = x0'
					end   = get_next_limite();

		
*/

int				eq_solve_deg3(t_eq *eq);
int				eq_solve_deg4(t_eq *eq);
