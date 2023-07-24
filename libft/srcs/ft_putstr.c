/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:29:53 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:04:26 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(const char *s, int *len)
{
	int	i;

	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		(*len) += 6;
		return (0);
	}
	i = 0;
	while (s[i])
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		(*len)++;
		i++;
	}
	return (0);
}
