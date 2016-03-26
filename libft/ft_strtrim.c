/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2015/11/05 00:11:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*copy;
	size_t	i;

	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	i = 0;
	while (s[i])
		i++;
	while (i > 0 && (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n'))
		i--;
	if (i == 0)
		return (NULL);
	copy = ft_strnew(i);
	if (!copy)
		return (NULL);
	copy = ft_strncpy(copy, s, i);
	copy[i] = '\0';
	return (copy);
}
