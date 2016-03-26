/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_memset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerle <amerle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 07:39:01 by amerle            #+#    #+#             */
/*   Updated: 2013/11/20 07:39:33 by amerle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static int	ft_test_memset2(char *str, char *str2, int n)
{
	int	res;

	res = 0;
	ft_memset(str, '{', n);
	memset(str2, '{', n);
	printf("After : \"%s\" , \"%s\"", str, str2);
	if (strcmp(str, str2))
		++res;
	ft_print_status(res);
	return (res);
}

int			ft_test_memset(void)
{
	int res;
	char str[] = "Bonjour";
	char str2[] = "bonjour";

	res = 0;
	ft_print_begin("ft_memset");
	res += ft_test_memset2(str, str2, 4);
	ft_print_end(res);
	return (res);
}

