/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:57:12 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/21 18:20:24 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_get_ray_color(t_data *data, t_ray *ray)
{
	int		ambient;
	int		color;
	int		shadow;

	if (!find_intersect(data, ray))
		return (0);
	ambient = color_scale(data->ambient.color.hex, data->ambient.intensity);
	color = color_product(ray->color.hex, ambient);
	shadow = !check_shadow(data, ray);
	color = color_add(color, shadow * add_light(&data->light, ray));
	return (color);
}

static void	_draw_this_pixel(t_data *data, int x, int y)
{
	t_ray	ray;

	ray = create_ray(data->cam, (double)x / WIDTH, (double)y / HEIGHT);
	pixel_put(&data->mlx, WIDTH - x, HEIGHT - y, _get_ray_color(data, &ray));
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
