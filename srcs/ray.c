/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/01 17:00:03 by colas            ###   ########.fr       */
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

	ray.origin = cam.coords;
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

/*
	1 - Getting to the left border, on half the viewport height.
	2 - Getting to the lower left corner, horizontally and vertically.
	3 - Making sure we are also on the lower left corner depth-wise.
*/
void	get_low_left_corner_pos(t_cam *cam, t_coords z_axis)
{
	cam->ll_corner = v_oper(cam->coords, v_scale(cam->hor_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, v_scale(cam->ver_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, z_axis, SUB);
}

/*	This function allows us to calculate and setup camera data.
	That will help us to trace rays later.
   
	1 - Converting FOV from degrees to radiants.
	2 - Getting aspect ratio.
	3/4 - Calculating viewport height, and then width using aspect ratio.
	5 - Normalizing camera vector.
	6/7/8 - Calculating axis : depth, horizontal and vertical.
	9/10 - Calculating horizontal and vertical FOV thanks to the axis.
	11 - Getting the lower left corner of the viewport.
*/
void	set_camera(t_cam *cam)
{
	double		theta;
	double		aspect_ratio;
	double		viewport[2];
	t_coords	axis[3];

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = WIDTH / HEIGHT;
	viewport[X] = 2 * tan(theta / 2);
	viewport[Y] = viewport[X] * aspect_ratio;
	cam->v_normal = v_norm(cam->vector);
	axis[Z] = v_norm(v_scale(cam->v_normal, -1));
	axis[X] = v_oper((t_coords){0, 1, 0}, axis[Z], CROSS);
	axis[Y] = v_oper(axis[Z], axis[X], CROSS);
	cam->hor_fov = v_scale(axis[X], viewport[X]);
	cam->ver_fov = v_scale(axis[Z], viewport[Y]);
	get_low_left_corner_pos(cam, axis[Z]);
}
