/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/08/30 21:12:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray create_ray(t_cam cam, double x, double y) 
{
	t_ray ray;

	ray.origin = cam.coords;
	ray.dir = v_oper(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y), ADD);
	ray.dir = v_oper(ray.dir, cam.ll_corner, ADD);
	ray.dir = v_norm(v_oper(ray.dir, ray.origin, SUB));
	// printf("or : rayx = %f, rayy = %f, rayz = %f\n dir : rayx = %f, rayy = %f, rayz = %f\n", ray.origin.x, ray.origin.y, ray.origin.z, ray.dir.x, ray.dir.y, ray.dir.z);
	return (ray);
}

void draw_rays(t_data *data) 
{
	int		x;
	int		y;
	t_ray	ray;
	// printf("sizex = %d, sizey = %d", data->mlx.size_y, data->mlx.size_x);

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

// void	get_low_left_corner_pos(t_cam *cam, t_coords z_vect)
// {
// 	cam->ll_corner = v_oper(cam->coords, v_scale(cam->hor_fov, 0.5), SUB);
// 	cam->ll_corner = v_oper(cam->ll_corner, v_scale(cam->ver_fov, 0.5), SUB);
// 	cam->ll_corner = v_oper(cam->ll_corner, z_vect, SUB);
// }

/*	This function allows us to calculate and setup camera data.
	That will help us to trace rays later.
   
	1 - Converting FOV from degrees to radiants.
	2 - Getting aspect ratio.
	3/4 - Calculating viewport height, and then width using aspect ratio.
	5 - Normalizing camera vector.
	6/7/8 - Calculating axis : depth, horizontal and vertical.
	9/10 - Calculating horizontal and vertical FOV thanks to the axis.
	11/12/13 - Helps us getting the lower left corner of the viewport.
	11 - Getting to the left border, on half the viewport height.
	12 - Getting to the lower left corner, horizontally and vertically.
	13 - Making sure we are also on the lower left corner depth-wise.
*/
void	set_camera(t_cam *cam)
{
	double		theta;
	double		aspect_ratio;
	double		viewport[2];
	t_coords	tmp[3];

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = WIDTH / HEIGHT;
	viewport[0] = 2 * tan(theta / 2);
	viewport[1] = viewport[0] * aspect_ratio;
	cam->v_normal = v_norm(cam->vector);
	tmp[0] = v_norm(v_scale(cam->v_normal, -1));
	tmp[1] = v_oper((t_coords){0, 1, 0}, tmp[0], CROSS);
	tmp[2] = v_oper(tmp[0], tmp[1], CROSS);
	cam->hor_fov = v_scale(tmp[1], viewport[0]);
	cam->ver_fov = v_scale(tmp[2], viewport[1]);
	cam->ll_corner = v_oper(cam->coords, v_scale(cam->hor_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, \
		v_scale(cam->ver_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, tmp[0], SUB);
}
