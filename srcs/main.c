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

int key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		terminate(data);
	return (0);
}

int	call_terminate(t_data *data)
{
	terminate(data);
	return (0);
}

void init_mlx(t_data *data)
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
	set_camera(&data.cam);
	// draw_rays(&data);
	mlx_loop(data.mlx.mlx_ptr);
	terminate(&data);
	return (0);
}
