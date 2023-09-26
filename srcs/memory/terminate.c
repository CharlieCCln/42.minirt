/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:24:56 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 17:07:46 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	terminate(t_data *data)
{
	int	code;

	code = 1;
	if (data->mlx.img_ptr)
		mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img_ptr);
	if (data->mlx.win_ptr)
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	if (data->mlx.mlx_ptr)
	{
		code = 0;
		mlx_destroy_display(data->mlx.mlx_ptr);
		free(data->mlx.mlx_ptr);
	}
	if (data->mlx.win_name)
		free(data->mlx.win_name);
	if (data->objects)
		free(data->objects);
	close(data->fd);
	exit(code);
}
