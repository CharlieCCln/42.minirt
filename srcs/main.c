/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:03 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/28 14:30:05 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "minirt.h"

void	print_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

int			mlx_exit(t_data *data) 
{
	if (data->mlx.win_ptr)
	{
		mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	}
	return (exit(0), 0);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		mlx_exit(data);
	return (0);
}

void init_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	mlx_get_screen_size(data->mlx.mlx_ptr, &data->mlx.size_x, &data->mlx.size_y);
	data->mlx.size_x /= 2;
	data->mlx.size_y /= 2;
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, data->mlx.size_x, data->mlx.size_y, "Window");
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, mlx_exit, data);
	mlx_key_hook(data->mlx.win_ptr, key_press, data);
	mlx_loop(data->mlx.mlx_ptr);
}

// t_coords create_coords(t_coords p1) 
// {
// 	t_coords res;
	
// 	return ()
// }

// t_coords v_add (t_coords p1, t_coords p2) 
// {
// 	return (create_coords(, ));
// }

// t_ray create_ray(t_cam cam, float x, float y) 
// {
// 	t_ray ray;

// 	ray.origin = cam.coords;
// 	ray.dir = v_add(x);
// }

void draw_rays(t_data *data) 
{
	int x;
	int y;
	t_ray ray;

	y = -1;
	while (y++ < data->mlx.size_y - 1)
	{
		x = -1;
		while (x++ < data->mlx.size_x - 1) 
		{
			// ray = create_ray(data->cam, (float)x / data->mlx.size_x, (float)y / data->mlx.size_y);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	bzero_everything(&data);
	if (argc != 2 || arg_check(argv[1]))
	{
		print_error("Please use \"./miniRT path/to/file.rt\"");
		terminate(&data);
	}
	parsing_hub(&data, argv[1]);
	init_mlx(&data);
	draw_rays(&data);
	terminate(&data);
	return (0);
}
