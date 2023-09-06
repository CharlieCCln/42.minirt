/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 14:30:25 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 14:30:32 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_plane(t_data *data, char **content)
{
	if (!content[1] || !content[2] || !content[3])
		print_error("Plane : not enough data");
	else if (content[4])
		print_error("Plane : too much data");
	if (!content[1] || !content[2] || !content[3] || content[4])
		return (1);
	data->objects[data->obj_nbr].type = PLANE;
	if (parse_coords(&data->objects[data->obj_nbr].coords, content[1]))
	{
		print_error("Plane : incorrect coordinates format or value");
		return (1);
	}
	if (parse_vector(&data->objects[data->obj_nbr].vector, content[2]))
	{
		print_error("Plane : incorrect vector format or value");
		return (1);
	}
	if (parse_color(&data->objects[data->obj_nbr].color, content[3]))
	{
		print_error("Plane : incorrect color format or value");
		return (1);
	}
	return (0);
}
