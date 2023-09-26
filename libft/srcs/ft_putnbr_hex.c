/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:03:26 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:04:00 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex(unsigned long long int n, int *len, int index, int s)
{
	char	c;

	if (n > 15 && s != -1)
	{
		if (ft_putnbr_hex(n / 16, len, index, s) == -1 || \
			ft_putnbr_hex(n % 16, len, index, s) == -1)
			return (-1);
	}
	if (n < 16 && s != -1)
	{
		if (n < 10)
			c = n + 48;
		if (n > 9 && index == 0)
			c = n + 87;
		if (n > 9 && index == 1)
			c = n + 55;
		if (write(1, &c, 1) == -1)
		{
			s = -1;
			return (-1);
		}
		(*len)++;
	}
	return (0);
}
