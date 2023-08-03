/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:33:21 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 12:34:16 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_coords_format(char *content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == '-')
			i++;
		if (content[i] < '0' || content[i] > '9')
			return (1);
		while (content[i] && ((content[i] >= '0' && content[i] <= '9') || \
			content[i] == '.'))
			i++;
		if (content[i] && (content[i] != ',' || j == 2))
			return (1);
		else if (content[i] && content[i + 1])
			j++;
		if (content[i])
			i++;
	}
	if (j < 2)
		return (1);
	return (0);
}

int	parse_coords(t_coords *coords, char *content)
{
	char	**split;

	if (check_coords_format(content))
		return (1);
	split = ft_split(content, ',');
	if (!split)
	{
		ft_putendl_fd("parse_coords ft_split fail", 2);
		return (1);
	}
	if (get_double_value(&coords->x, split[0]) || \
		get_double_value(&coords->y, split[1]) || \
		get_double_value(&coords->z, split[2]))
	{
		ft_freeall(split);
		return (1);
	}
	ft_freeall(split);
	return (0);
}

int	parse_vector(t_coords *vector, char *content)
{
	if (parse_coords(vector, content))
		return (1);
	if (vector->x < -1 || vector->x > 1 || \
		vector->y < -1 || vector->y > 1 || \
		vector->z < -1 || vector->z > 1)
		return (1);
	return (0);
}
