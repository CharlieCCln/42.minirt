/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:17:49 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/18 15:19:06 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	1 - Getting to the left border, on half the viewport height.
	2 - Getting to the lower left corner, horizontally and vertically.
	3 - Making sure we are also on the lower left corner depth-wise.
*/

static void	_get_low_left_corner_pos(t_cam *cam, t_coords z_axis)
{
	cam->ll_corner = v_oper(SUB, cam->origin, v_scale(cam->hor_fov, 0.5));
	cam->ll_corner = v_oper(SUB, cam->ll_corner, v_scale(cam->ver_fov, 0.5));
	cam->ll_corner = v_oper(SUB, cam->ll_corner, z_axis);
}

/*
    1 - Converting FOV from degrees to radiants.
	2 - Getting screen aspect ratio.
	3/4 - Calculating viewport height, and then width using aspect ratio.
	5 - Normalizing camera vector.
*/

static void	_calculating_viewport(t_cam *cam, double *viewport)
{
	double		theta;
	double		aspect_ratio;

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = (double)HEIGHT / WIDTH;
	viewport[X] = 2 * tan(theta / 2);
	viewport[Y] = viewport[X] * aspect_ratio;
	cam->dir_norm = v_norm(cam->dir);
}

// Calculating axis : depth, horizontal and vertical.

static void	_calculating_axis(t_cam *cam, t_coords *axis)
{
	axis[Z] = v_norm(v_scale(cam->dir_norm, -1));
	axis[X] = v_oper(CROSS, (t_coords){0, 1, 0}, axis[Z]);
	axis[Y] = v_oper(CROSS, axis[Z], axis[X]);
}

// Calculating horizontal and vertical FOV thanks to the axis.

static void	_calculating_fov(t_cam *cam, double *viewport, t_coords *axis)
{
	cam->hor_fov = v_scale(axis[X], viewport[X]);
	cam->ver_fov = v_scale(axis[Y], viewport[Y]);
}

/*	
    This function allows us to calculate and setup camera data.
	That will help us to trace rays later.
   
	The information stored in the camera structure are horizontal 
	and vertical fov values aswell as low left corner 
	position to facilitate calculations.
*/
void	set_camera(t_cam *cam)
{
	double		viewport[2];
	t_coords	axis[3];

	_calculating_viewport(cam, viewport);
	_calculating_axis(cam, axis);
	_calculating_fov(cam, viewport, axis);
	_get_low_left_corner_pos(cam, axis[Z]);
}
