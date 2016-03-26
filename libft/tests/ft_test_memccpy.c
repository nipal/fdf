/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_memccpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <amerle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 07:50:36 by amerle            #+#    #+#             */
/*   Updated: 2016/01/16 19:03:55 by tboos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_test_memccpy(void)
{
	int	res;
	t_memtest t1;
	t_memtest t2;

	t1.c = 'Y';
	t1.c3 = '{';
	t1.c2 = ',';
	t1.num2 = 5446;
	res = 0;
	ft_print_begin("ft_memccpy");
	bzero((void *)&t2, sizeof(t_memtest));
	ft_memccpy((void *)&t2, (const void *)&t1, '{', sizeof(t_memtest));
	if (!(t2.c == t1.c && t2.c3 == t1.c3 &&
		 t2.c2 != t1.c2 && t2.num2 != t1.num2))
		++res;
	ft_memccpy((void *)&t2, (const void *)&t1, ',', sizeof(t_memtest));
	if (!(t2.c == t1.c && t2.c3 == t1.c3 &&
		 t2.c2 == t1.c2 && t2.num2 != t1.num2))
		++res;
	printf("Test");
	ft_print_status(res);
	return (ft_print_end(res));
}
