/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:31:18 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:04:13 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbr_intmin(int *len)
{
	if (write(1, "-2147483648", 11) == -1)
		return (-1);
	(*len) += 11;
	return (0);
}

static int	ft_putnbr_negative(int *n, int *len)
{
	if (write(1, "-", 1) == -1)
		return (-1);
	(*len)++;
	*n = *n * -1;
	return (0);
}

int	ft_putnbr(int n, int *len, int s)
{
	char	c;

	if (n == -2147483648)
		return (ft_putnbr_intmin(len));
	if (n < 0)
		if (ft_putnbr_negative(&n, len) == -1)
			return (-1);
	if (n > 9 && s != -1)
		if (ft_putnbr(n / 10, len, s) == -1 || ft_putnbr(n % 10, len, s) == -1)
			return (-1);
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
	return (s);
}
