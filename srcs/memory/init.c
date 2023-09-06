/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:39:32 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/06 12:50:37 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "minirt.h"

void	init_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, \
		WIDTH, HEIGHT, data->mlx.win_name);
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img_ptr, &data->mlx.bpp, \
		&data->mlx.len, &data->mlx.end);
	data->mlx.bpp /= 8;
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, \
		call_terminate, data);
	mlx_key_hook(data->mlx.win_ptr, key_press, data);
}

void	allocate_objects(t_data *data, int *counts)
{
	int	i;

	data->objects = malloc(sizeof(t_object) * (counts[3] + 1));
	if (!data->objects)
	{
		print_error("data->objects malloc fail");
		terminate(data);
	}
	i = 0;
	while (i < counts[3])
	{
		ft_bzero(&data->objects[i].coords, sizeof(t_coords));
		ft_bzero(&data->objects[i].vector, sizeof(t_coords));
		ft_bzero(&data->objects[i].color, sizeof(t_color));
		data->objects[i].diameter = 0;
		data->objects[i].height = 0;
		i++;
	}
	data->objects[i].diameter = -1;
}

void	bzero_everything(t_data *data)
{
	ft_bzero(&data->mlx, sizeof(t_mlx));
	ft_bzero(&data->ambient.color, sizeof(t_color));
	ft_bzero(&data->ambient, sizeof(t_ambient));
	ft_bzero(&data->cam.coords, sizeof(t_coords));
	ft_bzero(&data->cam.vector, sizeof(t_coords));
	ft_bzero(&data->cam, sizeof(t_cam));
	ft_bzero(&data->light.coords, sizeof(t_coords));
	ft_bzero(&data->light, sizeof(t_light));
	data->objects = NULL;
	data->obj_index = -1;
}
