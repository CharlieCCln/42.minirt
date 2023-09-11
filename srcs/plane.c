/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:55:16 by colas             #+#    #+#             */
/*   Updated: 2023/09/11 19:12:05 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

int	intersect_plane(t_ray *ray, t_object *plane)
{
	t_coords	dist;
	double		hit_dist;

	hit_dist = 0;
	dist = v_oper(ray->origin, plane->coords, SUB);
	if (!get_plane_hit(ray, plane, dist, &hit_dist))
		return (0);
	return (check_nearest_plane_hit(ray, plane, hit_dist));
}

int		get_plane_hit(t_ray *ray, t_object *plane, t_coords dist, double *hit_dist)
{
	double	time;
	double	den;

	den = v_dot(v_norm(ray->dir), plane->normal);
	if (!den)
		return (0);
	time = v_dot(v_oper(plane->coords, ray->origin, SUB), plane->normal) / den;
	if (ray->hit.time > time && time > EPSILON)
	{
		ray->hit.time = time;
		ray->hit.point = get_hit_point(*ray);
		if (v_dot(ray->dir, plane->normal) > 0)
			plane->normal = v_scale(plane->normal, -1);
		ray->normal = plane->normal;
		ray->color = plane->color;
		return (1);
	}
	return (0);
}