/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:57:12 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/06 14:57:24 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_draw_this_pixel(t_data *data, int x, int y)
{
	t_ray	ray;

	ray = create_ray(data->cam, (double)x / WIDTH, (double)y / HEIGHT);
	pixel_put(&data->mlx, x, HEIGHT - y, get_ray_color(data, &ray));
}

void	drawing(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH - 1)
		{
			_draw_this_pixel(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, \
		data->mlx.img_ptr, 0, 0);
}
