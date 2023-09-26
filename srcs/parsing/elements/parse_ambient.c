/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:28:24 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 13:56:16 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_data *data, char **content)
{
	if (!content[1] || !content[2])
		print_error("Ambient : not enough data");
	else if (content[3])
		print_error("Ambient : too much data");
	if (!content[1] || !content[2] || content[3])
		return (1);
	if (get_double_value(&data->ambient.intensity, content[1]))
	{
		print_error("Ambient : incorrect intensity format or value");
		return (1);
	}
	if (data->ambient.intensity < 0 || data->ambient.intensity > 1)
	{
		print_error("Ambient : intensity not in 0.0 - 1.0 range");
		return (1);
	}
	if (parse_color(&data->ambient.color, content[2]))
	{
		print_error("Ambient : incorrect color format or value");
		return (1);
	}
	return (0);
}
