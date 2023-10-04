/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:33:18 by colas             #+#    #+#             */
/*   Updated: 2023/10/02 11:14:20 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function gets the potential hit position and updates is_side bool
	if the ray hits the side of the cylinder before hitting one of its caps
	or if the ray only goes through the cylinder by its side.
*/

static double	_get_cylinder_hit(t_ray *ray, t_object *cyl, bool *is_side)
{
	double	side_hit;
	double	caps_hit;

	side_hit = get_side_hit(ray, cyl);
	caps_hit = get_caps_hit(ray, cyl);
	if (side_hit < INFINITY || caps_hit < INFINITY)
	{
		if (side_hit < caps_hit)
		{
			*is_side = true;
			return (side_hit);
		}
		return (caps_hit);
	}
	return (INFINITY);
}

/*
	This functions helps us calculate the normal by checking which part
	of the cylinder our ray hits. Especially in the case where the ray
	goes through both the side and one of the caps of the cylinder.
*/

static t_coords	_closest_cyl_part(t_coords cyl_origin, \
	t_coords cyl_top, t_coords ray_hit)
{
	t_coords	hit2ori;
	t_coords	top2ori;
	double		mult;

	hit2ori = v_oper(SUB, ray_hit, cyl_origin);
	top2ori = v_oper(SUB, cyl_top, cyl_origin);
	mult = v_dot(hit2ori, top2ori) / v_dot(top2ori, top2ori);
	if (mult < 0)
		mult = 0;
	else if (mult > 1)
		mult = 1;
	return (v_oper(ADD, cyl_origin, v_scale(MULT, top2ori, mult)));
}

/*
	This function checks if our new distance to the hit is smaller than the
	previous distance. If that's the case, that means this cylinder is closer
	than the previous object we would show, so we get the color and distance
	of this cylinder to display it later. We also calculate the normal of the
	hit, that will help us later with the lights. The way we calculate this
	normal depends on the position on the hit : on the side of the cylinder or
	on one of its caps.
*/

static int	_check_nearest_cylinder_hit(t_ray *ray, t_object *cyl, \
	bool is_side, double hit_dist)
{
	t_coords	cyl_top;
	double		dir_len;

	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		dir_len = v_dist((t_coords){0, 0, 0}, cyl->dir);
		cyl->dir = v_scale(DIV, cyl->dir, dir_len);
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		cyl_top = v_oper(ADD, \
			cyl->origin, v_scale(MULT, cyl->dir, cyl->height));
		if (is_side)
			ray->hit_norm = v_oper(SUB, \
				_closest_cyl_part(cyl->origin, cyl_top, ray->hit), ray->hit);
		else
			ray->hit_norm = cyl->dir;
		if (v_dot(ray->dir, ray->hit_norm) > 0)
			ray->hit_norm = v_scale(MULT, ray->hit_norm, -1);
		ray->hit_norm = v_norm(ray->hit_norm);
		ray->color = cyl->color;
		return (1);
	}
	return (0);
}

int	intersect_cylinder(t_ray *ray, t_object *cyl)
{
	bool		is_side;
	double		hit_dist;

	is_side = false;
	hit_dist = _get_cylinder_hit(ray, cyl, &is_side);
	return (_check_nearest_cylinder_hit(ray, cyl, is_side, hit_dist));
}
