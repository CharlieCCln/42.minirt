/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:44:55 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 13:49:39 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_fov(int *fov, char *content)
{
	int	i;

	i = 0;
	*fov = 0;
	while (content[i])
	{
		if (content[i] < '0' || content[i] > '9')
			return (1);
		*fov = *fov * 10 + (content[i] - 48);
		if (*fov > 180)
			return (1);
		i++;
	}
	return (0);
}

int	parse_camera(t_data *data, char **content)
{
	if (!content[1] || !content[2] || !content[3])
		print_error("Camera : not enough data");
	else if (content[4])
		print_error("Camera : too much data");
	if (!content[1] || !content[2] || !content[3] || content[4])
		return (1);
	if (parse_coords(&data->cam.coords, content[1]))
	{
		print_error("Camera : incorrect coordinates format or value");
		return (1);
	}
	if (parse_vector(&data->cam.vector, content[2]))
	{
		print_error("Camera : incorrect vector format or value");
		return (1);
	}
	if (parse_fov(&data->cam.fov, content[3]))
	{
		print_error("Camera : incorrect FOV format or value");
		return (1);
	}
	return (0);
}
