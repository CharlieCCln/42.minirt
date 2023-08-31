/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:46 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/28 11:09:16 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_parse_line_content(t_data *data, char **content)
{
	if (!*content)
		return (0);
	else if (!ft_strcmp(*content, "A"))
		return (parse_ambient(data, content));
	else if (!ft_strcmp(*content, "C"))
		return (parse_camera(data, content));
	else if (!ft_strcmp(*content, "L"))
		return (parse_light(data, content));
	else if (!ft_strcmp(*content, "sp") || \
		!ft_strcmp(*content, "pl") || \
			!ft_strcmp(*content, "cy"))
		return (parse_object(data, content));
	return (0);
}

void	parse_elements(t_data *data, char *filename)
{
	char	*line;
	char	**content;

	data->fd = open_infile(data, filename);
	while (42)
	{
		line = gnl_safe(data, data->fd);
		if (!line)
			break ;
		content = ft_split(remove_endl(line), ' ');
		free(line);
		if (!content || _parse_line_content(data, content))
		{
			if (!content)
				print_error("ft_split fail");
			else
				ft_freeall(content);
			gnl_safe(data, -1);
			terminate(data);
		}
		ft_freeall(content);
	}
	gnl_safe(data, -1);
	close(data->fd);
}

void	parsing_hub(t_data *data, char *filename)
{
	check_elements(data, filename);
	parse_elements(data, filename);
	parse_filename(data, filename);
/* 
	int	i;
	printf("AMBIENT /////\n");
	printf("intensity = %f\n", data->ambient.intensity);
	printf("r = %d | g = %d | b = %d | hex = %d\n", \
		data->ambient.color.r, data->ambient.color.g, \
			data->ambient.color.b, data->ambient.color.hex);
	printf("CAMERA /////\n");
	printf("coords | x = %f | y = %f | z = %f\n", data->cam.coords.x, \
		data->cam.coords.y, data->cam.coords.z);
	printf("vector | x = %f | y = %f | z = %f\n", data->cam.vector.x, \
		data->cam.vector.y, data->cam.vector.z);
	printf("fov = %d\n", data->cam.fov);
	printf("LIGHT /////\n");
	printf("coords | x = %f | y = %f | z = %f\n", data->light.coords.x, \
		data->light.coords.y, data->light.coords.z);
	printf("intensity = %f\n", data->light.intensity);
	printf("OBJECTS /////\n");
	i = 0;
	while (data->objects[i].diameter != -1)
	{
		printf("type = %d\n", data->objects[i].type);
		printf("coords | x = %f | y = %f | z = %f\n", data->objects[i].coords.x, \
			data->objects[i].coords.y, data->objects[i].coords.z);
		printf("vector | x = %f | y = %f | z = %f\n", data->objects[i].vector.x, \
			data->objects[i].vector.y, data->objects[i].vector.z);
		printf("r = %d | g = %d | b = %d | hex = %d\n", \
			data->objects[i].color.r, data->objects[i].color.g, \
				data->objects[i].color.b, data->objects[i].color.hex);
		printf("size = %f * %f\n", data->objects[i].diameter, data->objects[i].height);
		printf("-----\n");
		i++;
	} */
}
