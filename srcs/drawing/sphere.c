/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:37:50 by charlie           #+#    #+#             */
/*   Updated: 2023/09/26 18:41:35 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function checks if our new distance to the hit is smaller than the
	previous distance. If that's the case, that means this sphere is closer
	than the previous object we would show, so we get the color and distance
	of this sphere to display it later. We also calculate the normal of the
	hit, that will help us later with the lights.
*/

static int	_check_nearest_sphere_hit(t_ray *ray, t_object *sphere, \
	double hit_dist)
{
	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(SUB, ray->hit, sphere->origin));
		if (v_dot(ray->dir, ray->hit_norm) > 0)
			ray->hit_norm = v_scale(MULT, ray->hit_norm, -1);
		ray->color = sphere->color;
		return (1);
	}
	return (0);
}

/*
	This function calculates the potential position of the hit on the sphere.
	It uses the Ray-Sphere equation, a quadratic equation that can have zero, 
	one or two solutions.
	If delta is less than 0, our ray does not intersect with the sphere.
	If delta is equal to 0, our ray is tangent to the sphere.
	If delta is more than 0, our ray intersect and goes through the sphere.
	That means we have two solutions. But we only use the solution with the
	smallest result between the two (-b - √delta / 2a), because if will be the
	closest hit that matters for our camera.
*/

static int	_sphere_equation(t_ray *ray, t_object *sphere, \
	t_coords sp2ray, double *hit_dist)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	is_inside;

	a = v_dot(ray->dir, ray->dir);
	b = 2 * v_dot(ray->dir, sp2ray);
	c = v_dot(sp2ray, sp2ray) - \
		((sphere->diameter / 2) * (sphere->diameter / 2));
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	*hit_dist = (-b - sqrtf(delta)) / (2 * a);
	is_inside = (-b + sqrtf(delta)) / (2 * a);
	if (is_inside >= 0 && *hit_dist < 0)
		*hit_dist = is_inside;
	return (1);
}

/*
	This function tends to find if our ray intersects with a given sphere.
	To do this, it first calculates the potential coords of the hit,
	and then, if there is a hit, checks if the hit is visible or behind
	another object.
*/

int	intersect_sphere(t_ray *ray, t_object *sphere)
{
	t_coords	sp2ray;
	double		hit_dist;

	hit_dist = 0;
	sp2ray = v_oper(SUB, ray->origin, sphere->origin);
	if (!_sphere_equation(ray, sphere, sp2ray, &hit_dist))
		return (0);
	return (_check_nearest_sphere_hit(ray, sphere, hit_dist));
}
