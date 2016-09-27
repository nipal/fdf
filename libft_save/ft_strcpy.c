/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpirsch <jpirsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:19:29 by jpirsch           #+#    #+#             */
/*   Updated: 2016/09/10 05:32:44 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
//	dprintf(1, "##begin cpy\n");
	while (src[i])
	{
//		dprintf(1, " i:%d ", i);
		dst[i] = src[i];
		i++;
		if (!src[i])
			dst[i] = src[i];
	}
//	dprintf(1, "##end cpy\n");
	return (dst);
}
