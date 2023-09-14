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

/* static void		bhaskara(double a, double b, double c, double *res)
{
	double		sqrt_discriminant;

	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
	*res = (-b - sqrt_discriminant) / (2 * a);
} */

static void	_get_cylinder_vectors(t_coords *vectors, t_ray *ray, \
	t_object *cylinder, t_coords dist)
{
	vectors[0] = v_scale(cylinder->dir, v_dot(ray->dir, cylinder->dir));
	vectors[0] = v_oper(SUB, ray->dir, vectors[0]);
	vectors[1] = v_scale(cylinder->dir, v_dot(dist, cylinder->dir));
	vectors[1] = v_oper(SUB, v_oper(SUB, ray->origin, cylinder->origin), \
		vectors[1]);
}

static int	_get_cylinder_hit(t_ray *ray, t_object *cylinder, \
	t_coords dist, double *hit_dist)
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
	*hit_dist = (-b - sqrt(delta)) / (2 * a);
	return (1);
}

static double	cy_calc(t_ray *ray, t_object *cy, double *y, bool *ret)
{
	t_coords	v_cy2ray;
	double		time;
	double		dist;

	_get_cylinder_hit(ray, cy, v_oper(SUB, ray->origin, cy->origin), &time);
	v_cy2ray = v_oper(SUB, cy->origin, ray->origin);
	dist = v_dot(cy->dir, v_oper(SUB, v_scale(ray->dir, time), v_cy2ray));
	*ret = (dist >= 0 && dist <= cy->height);
	*y = dist;
	return (time);
}

/* static int	_check_nearest_cylinder_hit(t_ray *ray, t_object *cylinder, \
	double dist, double hit_dist)
{
	if (ray->dist > hit_dist)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(SUB, ray->hit,
								v_oper(ADD, v_scale(cylinder->dir, dist), cylinder->origin)));
		ray->color = cylinder->color;
		return (1);
	}
	return (0);
}

int	intersect_cylinder(t_ray *ray, t_object *cylinder)
{
	t_coords	ray2cyl;
	t_coords	cyl2ray;
	double		dist;
	double		hit_dist;

	ray2cyl = v_oper(SUB, ray->origin, cylinder->origin);
	if (!_get_cylinder_hit(ray, cylinder, ray2cyl, &hit_dist))
		return (0);
	cyl2ray = v_oper(SUB, cylinder->origin, ray->origin);
	dist = v_dot(cylinder->dir, v_oper(SUB, v_scale(ray->dir, hit_dist), cyl2ray));
	if (dist < 0 || dist > cylinder->height)
		return (0);
	return (_check_nearest_cylinder_hit(ray, cylinder, hit_dist, dist));
} */

int	intersect_cylinder(t_ray *ray, t_object *cylinder)
{
	bool		ret;
	double		time;
	double		y;

	time = cy_calc(ray, cylinder, &y, &ret);
	if (ret && ray->dist > time)
	{
		ray->dist = time;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(SUB, ray->hit,
								v_oper(ADD, v_scale(cylinder->dir, y), cylinder->origin)));
		ray->color = cylinder->color;
	}
	return (ret);
}
