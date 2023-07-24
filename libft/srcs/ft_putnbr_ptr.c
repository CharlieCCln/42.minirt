/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:14:49 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:04:06 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_ptr(unsigned long long int n, int *len, int s)
{
	char	c;

	if (n > 15 && s != -1)
	{
		if (ft_putnbr_ptr(n / 16, len, s) == -1 || \
			ft_putnbr_ptr(n % 16, len, s) == -1)
			return (-1);
	}
	if (n < 16 && s != -1)
	{
		if (n < 10)
			c = n + 48;
		if (n > 9)
			c = n + 87;
		if (write(1, &c, 1) == -1)
		{
			s = -1;
			return (-1);
		}
		(*len)++;
	}
	return (0);
}
