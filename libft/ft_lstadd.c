/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2015/11/05 00:11:36 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **begin, t_list *new)
{
	new->next = *begin;
	*begin = new;
}

void	ft_lstadd_back(t_list **begin, t_list *new)
{
	t_list	*elem

	if (!begin || !new)
		return ;
	if (!*begin)
	{
		*begin = new;
		return ;
	}
	elem = *begin;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
}
