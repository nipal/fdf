/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/14 00:25:54 by jpirsch           #+#    #+#             */
/*   Updated: 2016/03/03 05:40:22 by jpirsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "c_maths.h"

void	matrix_display(t_matrix *a)
{
	int		i;
	int		j;

	if (!a)
		return ;
	i = 0;
	while (i < a->y)
	{
		j = 0;
		while (j < a->x)
		{
			printf("%f ", a->m[j + a->x * i]);
//			ft_putnbr(a->m[j + a->x * i]);
//			ft_putchar(' ');
			j++;
		}
		printf("\n");
//		ft_putchar('\n');
		i++;
	}
}
