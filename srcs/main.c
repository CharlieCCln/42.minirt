/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:03 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/30 10:15:22 by cgelin           ###   ########.fr       */
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
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
	mlx_hook(data->mlx.win_ptr, DestroyNotify, StructureNotifyMask, mlx_exit, data);
	mlx_key_hook(data->mlx.win_ptr, key_press, data);
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
	get_cam_infos(&data);
	// draw_rays(&data);
	mlx_loop(data.mlx.mlx_ptr);
	terminate(&data);
	return (0);
}
