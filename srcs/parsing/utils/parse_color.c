/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:43:55 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 11:49:28 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_color_format(char *content)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] < '0' || content[i] > '9')
			return (1);
		if (content[i] == '0' && content[i + 1] && content[i + 1] != ',')
			return (1);
		while (content[i] && content[i] >= '0' && content[i] <= '9')
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

static int	ft_atoi_safe(char *arg)
{
	int	i;
	int	res;
	int	overflow;

	i = 0;
	res = 0;
	while (arg[i])
	{
		overflow = res;
		res = res * 10 + (arg[i] - 48);
		if (res / 10 != overflow)
			return (-1);
		i++;
	}
	return (res);
}

int	parse_color(t_color *color, char *content)
{
	char	**split;

	if (check_color_format(content))
		return (1);
	split = ft_split(content, ',');
	if (!split)
	{
		ft_putendl_fd("parse_color ft_split fail", 2);
		return (1);
	}
	color->r = ft_atoi_safe(split[0]);
	color->g = ft_atoi_safe(split[1]);
	color->b = ft_atoi_safe(split[2]);
	ft_freeall(split);
	if (color->r > 255 || color->g > 255 || color->b > 255 || \
		color->r < 0 || color->g < 0 || color->b < 0)
		return (1);
	color->hex = (color->r << 16 | color->g << 8 | color->b);
	return (0);
}
