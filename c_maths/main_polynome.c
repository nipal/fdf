#include "c_maths.h"
#include "stdlib.h"

t_matrix	*init_coef(int ac, char **av)
{
	int			i;
	t_matrix	*coef;

	if (!(coef = matrix_init(1, ac)))
		return (NULL);
	i = 0;
	while (i < ac)
	{
		coef->m[i] = atof(av[i]);
		i++;
	}
	return (coef);
}

int	main(int ac, char **av)
{
	t_eq	*eq;

	if (ac >= 2)
	{
		eq = eq_init(ac - 2, init_coef(ac - 1, av + 1));
		eq_print_coef(eq);	
		eq_print_all_deriv(eq);	
	}
	return (0);
}
