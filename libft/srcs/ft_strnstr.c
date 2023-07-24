/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:15:56 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/15 17:53:03 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if ((!haystack || !needle) && len == 0)
		return (NULL);
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while ((haystack[i] == needle[j]) && needle[j] && i < len)
		{
			i++;
			j++;
		}
		if (needle[j] == 0)
			return (&((char *)haystack)[i - j]);
		k++;
		i = k;
		j = 0;
	}
	return (NULL);
}
