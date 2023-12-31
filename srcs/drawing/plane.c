/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:55:16 by colas             #+#    #+#             */
/*   Updated: 2023/10/03 14:18:19 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

/*
	This function checks whether the calculated point is the closest 
	object hit to the camera. If so, we assign the hit information to the ray.
	If the dot product of the ray direction and the plane direction is greater 
	than zero, it means the ray is approaching the plane from the same side as 
	the normal vector of the plane so we have to negate the plane direction 
	to get the right orientation of the plane.
*/

static int	_check_nearest_plane_hit(t_ray *ray, t_object *plane, \
	double hit_dist)
{
	double	dir_len;

	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		dir_len = v_dist((t_coords){0, 0, 0}, plane->dir);
		plane->dir = v_scale(DIV, plane->dir, dir_len);
		ray->hit_norm = plane->dir;
		if (v_dot(ray->dir, ray->hit_norm) > 0)
			ray->hit_norm = v_scale(MULT, ray->hit_norm, -1);
		ray->color = plane->color;
		return (1);
	}
	return (0);
}

/*
	Firstly we check if the ray is parallel to the plane by checking 
	the dot product of the direction of the ray and the plane. 
	Then we calculate the hit distance from the camera and assign it 
	to the hit_dist variable.
*/

static int	_get_plane_hit(t_ray *ray, t_object *plane, double *hit_dist)
{
	double	dot;

	dot = v_dot(ray->dir, plane->dir);
	if (!dot)
		return (0);
	*hit_dist = v_dot(v_oper(SUB, plane->origin, ray->origin), \
		plane->dir) / dot;
	return (1);
}

/*
	This is the plane calculation function, it gets the points were the ray 
	hits the plane and checks which object is the closest if there are multiple.
*/

int	intersect_plane(t_ray *ray, t_object *plane)
{
	double		hit_dist;

	hit_dist = 0;
	if (!_get_plane_hit(ray, plane, &hit_dist))
		return (0);
	return (_check_nearest_plane_hit(ray, plane, hit_dist));
}
