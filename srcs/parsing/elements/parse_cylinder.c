/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:30:03 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 16:23:41 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_cylinder_size(t_data *data, char **content)
{
	if (get_double_value(&data->objects[data->obj_index].diameter, content[3]))
	{
		print_error("Cylinder : incorrect diameter format or value");
		return (1);
	}
	if (get_double_value(&data->objects[data->obj_index].height, content[4]))
	{
		print_error("Cylinder : incorrect height format or value");
		return (1);
	}
	return (0);
}

static int	parse_cylinder_coords_vector(t_data *data, char **content)
{
	if (parse_coords(&data->objects[data->obj_index].coords, content[1]))
	{
		print_error("Cylinder : incorrect coordinates format or value");
		return (1);
	}
	if (parse_vector(&data->objects[data->obj_index].vector, content[2]))
	{
		print_error("Cylinder : incorrect vector format or value");
		return (1);
	}
	return (0);
}

int	parse_cylinder(t_data *data, char **content)
{
	if (!content[1] || !content[2] || !content[3] || !content[4] || !content[5])
		print_error("Cylinder : not enough data");
	else if (content[6])
		print_error("Cylinder : too much data");
	if (!content[1] || !content[2] || !content[3] || !content[4] || \
		!content[5] || content[6])
		return (1);
	data->objects[data->obj_index].type = CYLINDER;
	if (parse_cylinder_coords_vector(data, content))
		return (1);
	if (parse_cylinder_size(data, content))
		return (1);
	if (parse_color(&data->objects[data->obj_index].color, content[5]))
	{
		print_error("Cylinder : incorrect color format or value");
		return (1);
	}
	return (0);
}
