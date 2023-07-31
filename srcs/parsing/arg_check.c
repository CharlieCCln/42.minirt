/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:04:07 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 14:04:16 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	arg_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isascii(arg[i]))
			return (1);
		i++;
	}
	if (i < 3 || ft_strcmp(&arg[i - 3], ".rt"))
		return (1);
	return (0);
}
