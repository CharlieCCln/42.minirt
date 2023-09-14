/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:33:18 by colas             #+#    #+#             */
/*   Updated: 2023/09/13 20:11:09 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_nearest_cylinder_hit(t_ray *ray, \
	t_object *cylinder, double hit_dist)
{
	double		dist;
	t_coords	cyl2ray;

	cyl2ray = v_oper(SUB, cylinder->origin, ray->origin);
	dist = v_dot(cylinder->dir, v_oper(SUB, v_scale(ray->dir, hit_dist), cyl2ray));
	if ((dist >= 0 && dist <= cylinder->height) && ray->dist > hit_dist)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(SUB, ray->hit,
								v_oper(ADD, v_scale(cylinder->dir, dist), cylinder->origin)));
		ray->color = cylinder->color;
	}
	return ((dist >= 0 && dist <= cylinder->height));
}

static void	_get_cylinder_vectors(t_coords *vectors, t_ray *ray, \
	t_object *cylinder, t_coords dist)
{
	vectors[0] = v_scale(cylinder->dir, v_dot(ray->dir, cylinder->dir));
	vectors[0] = v_oper(SUB, ray->dir, vectors[0]);
	vectors[1] = v_scale(cylinder->dir, v_dot(dist, cylinder->dir));
	vectors[1] = v_oper(SUB, v_oper(SUB, ray->origin, cylinder->origin), \
		vectors[1]);
}

static double	_get_cylinder_hit(t_ray *ray, t_object *cylinder, \
	t_coords dist)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	t_coords	vectors[2];

	_get_cylinder_vectors(vectors, ray, cylinder, dist);
	a = v_square(vectors[0]);
	b = 2 * v_dot(vectors[0], vectors[1]);
	c = v_square(vectors[1]) - \
		(cylinder->diameter / 2) * (cylinder->diameter / 2);
	delta = (b * b) - (4 * a * c);
	return ((-b - sqrt(delta)) / (2 * a));
}

int	intersect_cylinder(t_ray *ray, t_object *cylinder)
{
	double		hit_dist;

	hit_dist = _get_cylinder_hit(ray, cylinder, \
		v_oper(SUB, ray->origin, cylinder->origin));
	return (_check_nearest_cylinder_hit(ray, cylinder, hit_dist));
}
