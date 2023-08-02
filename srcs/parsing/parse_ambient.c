/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:28:24 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/02 18:36:00 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_color_format(char *content)
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

int	ft_atoi_safe(char *arg)
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
	{
		print_error("Incorrect color format");
		return (1);
	}
	split = ft_split(content, ',');
	if (!split)
	{
		print_error("parse_color ft_split fail");
		return (1);
	}
	color->r = ft_atoi_safe(split[0]);
	color->g = ft_atoi_safe(split[1]);
	color->b = ft_atoi_safe(split[2]);
	ft_freeall(split);
	if (color->r > 255 || color->g > 255 || color->b > 255 || \
		color->r < 0 || color->g < 0 || color->b < 0)
	{
		print_error("Incorrect color value");
		return (1);
	}
	color->hex = (color->r << 16 | color->g << 8 | color->b);
	return (0);
}

int	check_double_format(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-')
		i++;
	if (content[i] < '0' || content[i] > '9')
		return (1);
	if (content[i] == '0' && content[i + 1] && content[i + 1] != '.')
		return (1);
	while (content[i] && content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i] && (content[i] != '.' || !content[i + 1]))
		return (1);
	if (content[i])
		i++;
	while (content[i] && content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i])
		return (1);
	return (0);
}

int	minirt_atod(double *value, char *content)
{
	int		i;
	double	overflow;

	i = 0;
	if (content[i] == '-')
		i++;
	while (content[i] && content[i] != '.')
	{
		overflow = *value;
		*value = *value * 10 + (content[i] - 48);
		if ((int)(*value / 10) != overflow)
		{
			print_error("Double overflow");
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_double_value(double *value, char *content)
{
	int		i;
	int		pos;
	double	before;
	double	after;

	if (check_double_format(content))
	{
		print_error("Incorrect float/double format");
		return (1);
	}
	i = 0;
	pos = 1;
	before = 0;
	after = 0;
	if (content[0] == '-')
		pos = -1;
	if (minirt_atod(&before, content))
		return (1);
	while (content[i] && content[i] != '.')
		i++;
	if (content[i] && minirt_atod(&after, &content[i + 1]))
		return (1);
	*value = pos * (before + (after / pow(10, ft_strlen(&content[i + 1]))));
	return (0);
}

int	parse_ambient(t_data *data, char **content)
{
	if (!content[1] || !content[2])
		print_error("Ambient : not enough data");
	else if (content[3])
		print_error("Ambient : too much data");
	if (!content[1] || !content[2] || content[3])
		return (1);
	if (get_double_value(&data->ambient.intensity, content[1]))
		return (1);
	if (data->ambient.intensity < 0 || data->ambient.intensity > 1)
	{
		print_error("Ambient lighting ratio not in 0.0 - 1.0 range");
		return (1);
	}
	if (parse_color(&data->ambient.color, content[2]))
		return (1);
	printf("intensity = %f\n", data->ambient.intensity);
	printf("r = %d g = %d b = %d hex = %d\n", \
		data->ambient.color.r, data->ambient.color.g, \
			data->ambient.color.b, data->ambient.color.hex);
	return (0);
}
