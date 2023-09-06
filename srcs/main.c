/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:03 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/06 12:50:19 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
