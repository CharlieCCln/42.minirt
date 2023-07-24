/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:12:27 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/15 17:51:21 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len != 0 && dst < src)
	{
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else if (len != 0 && dst > src)
	{
		while (len != 0)
		{
			((char *)dst)[len - 1] = ((const char *)src)[len - 1];
			len--;
		}
	}
	return (dst);
}
