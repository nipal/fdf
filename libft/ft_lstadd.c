/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/26 21:24:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **begin, t_list *new)
{
	if (new && begin && *begin)
	{
		new->next = *begin;
		*begin = new;
	}
}

void	ft_lstadd_end(t_list **begin, t_list *new)
{
	t_list	*elem;
	
	if (!begin)
		return ;
	if (!(*begin))
	{
		*begin = new;
		return ;
	}
	elem = *begin;
	while (elem->next)
		elem = elem->next;
	elem->next = new;
}
