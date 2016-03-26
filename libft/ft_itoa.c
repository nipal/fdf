/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/01/19 20:19:07 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_nbrchar(char *nbr, int n, int i)
{
	while (n)
	{
		nbr[i] = '0' - (n % 10);
		n = n / 10;
		i--;
	}
	return (nbr);
}

char		*ft_itoa(int n)
{
	int		m;
	int		i;
	char	*nbr;

	i = -1;
	m = n;
	while (m)
	{
		m = m / 10;
		i++;
	}
	if (n <= 0)
		i++;
	nbr = ft_strnew(i + 2);
	nbr[i + 1] = '\0';
	if (n < 0)
		nbr[0] = '-';
	if (n > 0)
		n = -n;
	if (!n)
		nbr[0] = '0';
	return (ft_nbrchar(nbr, n, i));
}
