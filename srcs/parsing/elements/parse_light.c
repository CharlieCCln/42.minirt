/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:49:58 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 13:56:34 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_light(t_data *data, char **content)
{
	if (!content[1] || !content[2])
		print_error("Light : not enough data");
	else if (content[3])
		print_error("Light : too much data");
	if (!content[1] || !content[2] || content[3])
		return (1);
	if (parse_coords(&data->light.coords, content[1]))
	{
		print_error("Light : incorrect coordinates format or value");
		return (1);
	}
	if (get_double_value(&data->light.intensity, content[2]))
	{
		print_error("Light : incorrect intensity format or value");
		return (1);
	}
	if (data->light.intensity < 0 || data->light.intensity > 1)
	{
		print_error("Light : intensity not in 0.0 - 1.0 range");
		return (1);
	}
	return (0);
}
