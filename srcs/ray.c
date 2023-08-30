/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/08/30 17:37:12 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_ray create_ray(t_cam cam, float x, float y) 
{
	t_ray ray;

	ray.origin = cam.coords;
	ray.dir = v_operation(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y), ADD);
	
	// printf("or : rayx = %f, rayy = %f, rayz = %f\n dir : rayx = %f, rayy = %f, rayz = %f\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

void draw_rays(t_data *data) 
{
	int x;
	int y;
	t_ray ray;
	// printf("sizex = %d, sizey = %d", data->mlx.size_y, data->mlx.size_x);

	y = -1;
	while (y++ < data->mlx.size_y - 1)
	{
		x = -1;
		while (x++ < data->mlx.size_x - 1) 
		{
			ray = create_ray(data->cam, (float)x / data->mlx.size_x, (float)y / data->mlx.size_y);
		}
	}
}

void	get_cam_infos(t_data *data)
{
	double		theta;
	double		aspect_ratio;
	double		fov[2];
	t_coords	tmp[3];

	theta = (M_PI / 180) * data->cam.fov;
	aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;
	fov[0] = 2 * tan(theta / 2);
	fov[1] = fov[0] * aspect_ratio;
	tmp[0] = v_norm(v_scale(data->cam.normal, -1));
	tmp[1] = v_operation((t_coords){0, 1, 0}, tmp[0], CROSS);
	tmp[2] = v_operation(tmp[0], tmp[1], CROSS);
	data->cam.hor_fov = v_scale(tmp[1], fov[0]);
	data->cam.ver_fov = v_scale(tmp[2], fov[1]);
}
