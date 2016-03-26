/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/01/19 23:22:02 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_strsplitclean(char **split, char *copy, size_t nmot)
{
	size_t	i;

	i = 0;
	while (i < nmot)
	{
		split[i] = ft_strdup(split[i]);
		i++;
	}
	split[i] = NULL;
	free(copy);
	return (split);
}

static char	**ft_strsplitcpy(char *copy, char c, size_t j, size_t i)
{
	char	**split;

	split = (char **)malloc(sizeof(char *) * (j + 1));
	if (!split)
		return (NULL);
	j = 0;
	while (copy[i])
	{
		split[j] = &(copy[i]);
		while (copy[i] != c && copy[i])
			i++;
		if (!copy[i])
			return (ft_strsplitclean(split, copy, j + 1));
		copy[i] = '\0';
		i++;
		j++;
		while (copy[i] == c)
			i++;
	}
	split[j] = NULL;
	return (split);
}

char		**ft_strsplit(char const *s, char c)
{
	char	*copy;
	size_t	i;
	size_t	j;

	while (*s == c)
		s++;
	copy = ft_strdup(s);
	i = ft_strlen(copy);
	while (i && copy[i - 1] == c)
		i--;
	copy[i] = '\0';
	j = 1;
	while (i > 0)
	{
		if (copy[i] == c)
		{
			j++;
			while (copy[i] == c)
				i--;
		}
		i--;
	}
	return (ft_strsplitcpy(copy, c, j, i));
}
