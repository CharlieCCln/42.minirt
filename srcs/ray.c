/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/08/30 15:07:55 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



t_ray create_ray(t_cam cam, float x, float y) 
{
	t_ray ray;

	ray.origin = cam.coords;
	ray.dir = v_add(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y));
	
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

void get_cam_infos(t_data *data) 
{
	float theta;
	float aspect_ratio;
	
	theta = (M_PI / 180) * data->cam.fov;
	aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;
	w = v_norm(v_scale(cam->normal, -1));
	u = v_cross(gen_coord(0, 1, 0), w);
	v = v_cross(w, u);
	data->cam.hor_fov = 2 * tan(theta / 2);
	data->cam.hor_fov = data->cam.ver_fov * aspect_ratio;
}