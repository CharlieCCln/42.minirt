/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:44:34 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/15 17:40:53 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*new;

	map = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			new = ft_lstnew(f(lst->content));
			ft_lstadd_back(&map, new);
			if (!map)
			{
				ft_lstclear(&map, del);
				return (NULL);
			}
			lst = lst->next;
		}
	}
	return (map);
}
