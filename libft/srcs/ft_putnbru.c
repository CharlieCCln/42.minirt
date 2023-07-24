/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:00:52 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:04:19 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbru(unsigned int n, int *len, int s)
{
	char	c;

	if (n > 9 && s != -1)
	{
		if (ft_putnbru(n / 10, len, s) == -1 || \
			ft_putnbru(n % 10, len, s) == -1)
			return (-1);
	}
	if (n < 10 && s != -1)
	{
		c = n + 48;
		if (write(1, &c, 1) == -1)
		{
			s = -1;
			return (-1);
		}
		(*len)++;
	}
	return (0);
}
