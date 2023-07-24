/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:56:24 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/15 17:51:17 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (dst != NULL || src != NULL)
	{
		while (i < n)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	return (dst);
}
