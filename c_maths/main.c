
#include <stdio.h>
#include <math.h>
#include "c_maths.h"
#include "libft.h"

int	main()
{
	t_matrix	*a = NULL;
	t_matrix	*b = NULL;
	t_matrix	*c = NULL;
	double		kk;
	

	a = matrix_put_in_new(-1, 4, 1, 0);
	b = matrix_put_in_new(7, -6, 3, 0);
	vector_product_in(a, b, c);
	/*
	int	i = 0;
	a = matrix_init(4, 6);
	b = matrix_init(6, 4);
	c = matrix_init(b->x, a->y);
	while (i < a->x * a->y)
	{
		a->m[i] = i / a->x;
		b->m[i] = i % b->x;
		i++;
	}
	*/
	

//	c = matrix_product(a, b);
//	matrix_product_in(a, b, c);
	matrix_display(a);
	write(1, ".\n", 2);
	matrix_display(b);
	write(1, ".\n", 2);
	matrix_display(c);
	dprintf(1, ":::%f\n", kk);
	matrix_free(&a);
	matrix_free(&b);
	matrix_free(&c);

	return (0);
}
