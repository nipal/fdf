/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_anti_leaks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 15:02:25 by fjanoty           #+#    #+#             */
/*   Updated: 2016/09/10 07:33:32 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	soit le fd est au debut
//	soit il est aux milieux
//	soit il est a la fin mais en faitc'est comme au milieux

#include "get_next_line.h"

void	free_one_node(t_fdgnl **begin, int fd)
{
	t_fdgnl	*prev;
	t_fdgnl	*elem;

	elem = *begin;
	prev = NULL;
	while (elem->next && elem->fd != fd)
	{
		prev = elem;
		elem = elem->next;
	}
	if (elem->fd == fd)
	{
		if (!prev)
		{
			*begin = elem->next;
			free(elem->rest);
			free(elem);
		}
		else
		{
			prev->next = elem->next;
			free(elem->rest);
			free(elem);
		}
	}
}
