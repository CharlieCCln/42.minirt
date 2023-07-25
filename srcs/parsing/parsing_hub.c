/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:46 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/25 15:20:30 by ccrottie         ###   ########.fr       */
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

void	parsing_hub(t_data *data, char *filename)
{
	(void)data;
	(void)filename;
}
