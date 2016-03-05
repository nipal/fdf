
#include <stdio.h>
#include <math.h>
#include "c_maths.h"
#include "libft.h"

int	main()
{
	/*
	t_matrix	*s;
	t_matrix	*r;
	t_matrix	*t;
	t_matrix	*g;

	s = set_scale(3, 4, 5);
//	ft_putstr("scale : \n");
	printf("scale : \n");
	matrix_display(s);

	r = set_rotate(M_PI / 2, 4, 5);
//	ft_putstr("rotate : \n");
	printf("rotate : \n");
	matrix_display(r);

	t = set_translate(3, 4, 5);
	printf("translate : \n");
//	ft_putstr("translate : \n");
	matrix_display(t);

	g = matrix_init(4, 4);
	g = matrix_product(s, r);
	g = matrix_product(g, t);
	printf("global : \n");
	matrix_display(g);
*/
	t_coefs		coefs;
	t_roots		r;

	coefs.a = 2;
	coefs.b = -3;
	coefs.c = -3;
	coefs.d = 2;

	r = eq_solve_3rd(coefs);
	if (r.is_real)
//		printf("delta : %f delta0 : %f \n", r.x3, r.x4);
		printf("x1 : %f, x2 : %f , x3 : %f , delta : %f\n", r.x1, r.x2, r.x3, r.x4);
	else
		ft_putstr("No real solutions");

/*	t_matrix	*a;
	t_matrix	*b;
	t_matrix	*c;
	int		i;
	int		j;

	a = matrix_init(3, 3);
	b = matrix_init(3, 3);
	i = 0;
	while (i < a->x)
	{
		j = 0;
		while (j < a->y)
		{
			a->m[i + j * a->x] = i + j * a->x;
			j++;
		}
		i++;
	}
	matrix_display(a);
	ft_putstr("\n");
	b = matrix_add(a, b);
	b = matrix_add(a, b);
	matrix_display(b);
	ft_putstr("\n");
	c = matrix_product(a, b);
	ft_putstr("\n");
	matrix_display(c);
	c = matrix_scalar_product(a, 0.5);
	ft_putstr("\n");
	matrix_display(c);
	*/
	return (0);
}
