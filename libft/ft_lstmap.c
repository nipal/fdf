/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/04 18:24:51 by fjanoty           #+#    #+#             */
/*   Updated: 2016/01/19 23:17:57 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*copy;
	t_list	*front;
	t_list	*back;

	copy = NULL;
	if (lst)
	{
		copy = f(lst);
		copy = ft_lstnew(copy->content, copy->content_size);
		if (!copy)
			return (NULL);
		lst = lst->next;
	}
	front = copy;
	while (lst)
	{
		back = front;
		front = f(lst);
		front = ft_lstnew(front->content, front->content_size);
		if (!front)
			return (NULL);
		back->next = front;
		lst = lst->next;
	}
	return (copy);
}
