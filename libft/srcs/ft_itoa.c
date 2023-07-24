/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:07:16 by charlie           #+#    #+#             */
/*   Updated: 2022/11/15 17:50:29 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putitoa(int n, int len, char *str)
{
	int				i;
	unsigned int	nbr;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		nbr = n * -1;
		i++;
	}
	else
		nbr = n;
	while (i <= len)
	{
		str[i] = 0;
		i++;
	}
	i -= 2;
	while (i >= 0 && str[i] != '-')
	{
		str[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		nbr;
	char	*str;

	len = 0;
	nbr = n;
	while (nbr != 0)
	{
		len++;
		nbr = nbr / 10;
	}
	if (n <= 0)
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (ft_putitoa(n, len, str));
}
