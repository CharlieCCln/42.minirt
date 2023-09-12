#include "minirt.h"

/*
	1 - Getting to the left border, on half the viewport height.
	2 - Getting to the lower left corner, horizontally and vertically.
	3 - Making sure we are also on the lower left corner depth-wise.
*/
void	get_low_left_corner_pos(t_cam *cam, t_coords z_axis)
{
	cam->ll_corner = v_oper(cam->origin, v_scale(cam->hor_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, v_scale(cam->ver_fov, 0.5), SUB);
	cam->ll_corner = v_oper(cam->ll_corner, z_axis, SUB);
}

/*
    1 - Converting FOV from degrees to radiants.
	2 - Getting screen aspect ratio.
	3/4 - Calculating viewport height, and then width using aspect ratio.
	5 - Normalizing camera vector.
*/
void	calculating_viewport(t_cam *cam, double *viewport)
{
	double		theta;
	double		aspect_ratio;

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = WIDTH / HEIGHT;
	viewport[X] = 2 * tan(theta / 2);
	viewport[Y] = viewport[X] * aspect_ratio;
	cam->dir_norm = v_norm(cam->dir);
}

// Calculating axis : depth, horizontal and vertical.
void	calculating_axis(t_cam *cam, t_coords *axis) 
{
	axis[Z] = v_norm(v_scale(cam->dir_norm, -1));
	axis[X] = v_oper((t_coords){0, 1, 0}, axis[Z], CROSS);
	axis[Y] = v_oper(axis[Z], axis[X], CROSS);
}

// Calculating horizontal and vertical FOV thanks to the axis.
void    calculating_fov(t_cam *cam, double *viewport, t_coords *axis)
{
    cam->hor_fov = v_scale(axis[X], viewport[X]);
	cam->ver_fov = v_scale(axis[Y], viewport[Y]);
}

/*	
    This function allows us to calculate and setup camera data.
	That will help us to trace rays later.
   
	The information stored in the camera structure are horizontal and vertical fov values
    aswell as low left corner position to facilitate calculations.
*/
void	set_camera(t_cam *cam)
{
	double      viewport[2];
	t_coords    axis[3];
	
	// calculating_viewport(cam, viewport);
	// calculating_axis(cam, axis);
	double		theta;
	double		aspect_ratio;

	theta = (M_PI / 180) * cam->fov;
	aspect_ratio = (double)HEIGHT / WIDTH;
	viewport[X] = 2 * tan(theta / 2);
	viewport[Y] = viewport[X] * aspect_ratio;
	cam->dir_norm = v_norm(cam->dir);
	axis[Z] = v_norm(v_scale(cam->dir_norm, -1));
	axis[X] = v_oper((t_coords){0, 1, 0}, axis[Z], CROSS);
	axis[Y] = v_oper(axis[Z], axis[X], CROSS);
	calculating_fov(cam, viewport, axis);
	get_low_left_corner_pos(cam, axis[Z]);
}
