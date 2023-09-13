/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:37:50 by charlie           #+#    #+#             */
/*   Updated: 2023/09/13 18:59:04 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_nearest_sphere_hit(t_ray *ray, t_object *sphere, \
	double hit_dist)
{
	if (ray->dist > hit_dist)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(ray->hit, sphere->origin, SUB));
		ray->color = sphere->color;
		return (1);
	}
	return (0);
}

int	get_sphere_hit(t_ray *ray, t_object *sphere, \
	t_coords dist, double *hit_dist)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = v_square(ray->dir);
	b = 2 * v_dot(ray->dir, dist);
	c = v_dot(dist, dist) - \
		((sphere->diameter / 2) * (sphere->diameter / 2));
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	*hit_dist = (-b - sqrt(delta)) / (2 * a);
	return (1);
}

int	intersect_sphere(t_ray *ray, t_object *sphere)
{
	t_coords	dist;
	double		hit_dist;

	hit_dist = 0;
	dist = v_oper(ray->origin, sphere->origin, SUB);
	if (!get_sphere_hit(ray, sphere, dist, &hit_dist))
		return (0);
	return (_check_nearest_sphere_hit(ray, sphere, hit_dist));
}
