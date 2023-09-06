/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:30:48 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 14:30:55 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_data *data, char **content)
{
	if (!content[1] || !content[2] || !content[3])
		print_error("Sphere : not enough data");
	else if (content[4])
		print_error("Sphere : too much data");
	if (!content[1] || !content[2] || !content[3] || content[4])
		return (1);
	data->objects[data->obj_nbr].type = SPHERE;
	if (parse_coords(&data->objects[data->obj_nbr].coords, content[1]))
	{
		print_error("Sphere : incorrect coordinates format or value");
		return (1);
	}
	if (get_double_value(&data->objects[data->obj_nbr].diameter, content[2]))
	{
		print_error("Sphere : incorrect diameter format or value");
		return (1);
	}
	if (parse_color(&data->objects[data->obj_nbr].color, content[3]))
	{
		print_error("Sphere : incorrect color format or value");
		return (1);
	}
	return (0);
}
