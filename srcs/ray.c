/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/06 13:20:39 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* This fonction creates a Ray that goes in the camera direction.

1 - Ajusting the ray direction taking count of the screen pixel position
2 - Adding the low left corner to the ray to fit our matrice
3 - Substracting the ray direction by the ray origin so the origin of the ray is camera relative
then normalising it to make it simpler for calculations
*/
t_ray create_ray(t_cam cam, double x, double y) 
{
	t_ray ray;

	ray.origin = cam.ori;
	ray.dir = v_oper(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y), ADD);
	ray.dir = v_oper(ray.dir, cam.ll_corner, ADD);
	ray.dir = v_norm(v_oper(ray.dir, ray.origin, SUB));
	return (ray);
}

void draw_rays(t_data *data) 
{
	int		x;
	int		y;
	t_ray	ray;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x++ < WIDTH - 1) 
		{
			ray = create_ray(data->cam, (double)x / WIDTH, (double)y / HEIGHT);
			//project_ray(data, &ray);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, \
		data->mlx.img_ptr, 0, 0);
}


