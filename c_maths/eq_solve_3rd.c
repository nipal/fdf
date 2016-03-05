/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq_solve_3rd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/04 00:22:47 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "c_maths.h"
#include <math.h>
#include <complex.h> 
#include <stdio.h> 

t_roots	eq_solve_3rd(t_coefs coefs)
{
	double	delta;
	double	delta0;
	double	delta1;
	double	C;
	double	C_bar;
	double	complex u2;
	double	complex u3;
	t_roots	r;

	r.x4 = 0;
	r.is_real = 1;
	delta = 18.0 * coefs.a * coefs.b * coefs.c * coefs.d - 4.0 * coefs.b*coefs.b*coefs.b * coefs.d +\
			coefs.b*coefs.b * coefs.c*coefs.c - 4.0 * coefs.a * coefs.c*coefs.c*coefs.c - 27.0 * coefs.a*coefs.a * coefs.d*coefs.d;
		r.x4 = delta;
	delta0 = coefs.b * coefs.b - 3.0 * coefs.a * coefs.c;
	delta1 = 2.0 * coefs.b * coefs.b * coefs.b - 9.0 * coefs.a * coefs.b * coefs.c + 27.0 * coefs.a * coefs.a * coefs.d;
	u2 = -1.0 - I * sqrt(3.0) / 2.0;
	u3 = -1.0 + I * sqrt(3.0) / 2.0;
	printf("Starting values: Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(u2), cimag(u2), creal(u3), cimag(u3));
	C = cbrt((delta1 + sqrt(delta1 * delta1 + 4 * delta0 * delta0 *delta0)) / 2);
	C_bar = cbrt((delta1 + sqrt(delta1 * delta1 - 4 * delta0 * delta0 *delta0)) / 2);
	r.x1 = (-1.0 / 3.0 * coefs.a) * (coefs.b + C + C_bar);
//	printf("b * C + C_bar : %f, %f\n", creal((coefs.b + C + C_bar)), cimag((coefs.b + C + C_bar)));
	printf("C + C_bar : %f, %f\n", creal((C + C_bar)), cimag((C + C_bar)));
	r.x2 = (-1.0 / 3.0 * coefs.a) * (coefs.b + u3 * C + u2 * C_bar);
	r.x3 = (-1.0 / 3.0 * coefs.a) * (coefs.b + u2 * C + u3 * C_bar);
	/*delta = coefs.b * coefs.b - 4 * coefs.a * coefs.c;
	if (delta > 0)
	{
//		r.x1 = (-coefs.b - sqrt(delta)) / (2 * coefs.a);
//		r.x2 = (-coefs.b + sqrt(delta)) / (2 * coefs.a);
	}
	else if (delta == 0)
	{
		r.x1 = (-coefs.b) / (2 * coefs.a);
		r.x2 = 0;
	}
	else if (delta < 0)
		r.is_real = 0;
		*/
	return (r);
}
