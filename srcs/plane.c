/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlie <charlie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:55:16 by colas             #+#    #+#             */
/*   Updated: 2023/09/12 15:30:42 by charlie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

static int	_check_nearest_plane_hit(t_ray *ray, t_object *plane, \
	double hit_dist)
{
	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		if (v_dot(ray->dir, plane->dir) > 0)
			plane->dir = v_scale(plane->dir, -1);
		ray->hit_norm = plane->dir;
		ray->color = plane->color;
		return (1);
	}
	return (0);
}

static int	_get_plane_hit(t_ray *ray, t_object *plane, double *hit_dist)
{
	double	dot;

	dot = v_dot(v_norm(ray->dir), plane->dir);
	if (!dot)
		return (0);
	*hit_dist = v_dot(v_oper(plane->origin, ray->origin, SUB), \
		plane->dir) / dot;
	return (1);
}

int	intersect_plane(t_ray *ray, t_object *plane)
{
	double		hit_dist;

	hit_dist = 0;
	if (!_get_plane_hit(ray, plane, &hit_dist))
		return (0);
	return (_check_nearest_plane_hit(ray, plane, hit_dist));
}
