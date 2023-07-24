/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:53:41 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/30 17:35:53 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	int				i;
	long long int	num;
	int				pos;

	i = 0;
	num = 0;
	pos = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pos = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num != ((num * 10 + (pos * (str[i] - 48))) / 10))
			return (((pos + 1) / 2 / -1));
		num = num * 10 + (str[i] - 48) * pos;
		i++;
	}
	return (num);
}
