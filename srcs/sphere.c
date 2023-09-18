/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:37:50 by charlie           #+#    #+#             */
/*   Updated: 2023/09/18 13:33:36 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_nearest_sphere_hit(t_ray *ray, t_object *sphere, \
	double hit_dist)
{
	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(SUB, ray->hit, sphere->origin));
		ray->color = sphere->color;
		return (1);
	}
	return (0);
}

static int	_get_sphere_hit(t_ray *ray, t_object *sphere, \
	t_coords dist, double *hit_dist)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	test;

	a = v_square(ray->dir);
	b = 2 * v_dot(ray->dir, dist);
	c = v_dot(dist, dist) - \
		((sphere->diameter / 2) * (sphere->diameter / 2));
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	*hit_dist = (-b - sqrt(delta)) / (2 * a);
	test = (-b + sqrt(delta)) / (2 * a);
	if (test < *hit_dist)
		*hit_dist = test;
	return (1);
}

int	intersect_sphere(t_ray *ray, t_object *sphere)
{
	t_coords	dist;
	double		hit_dist;

	hit_dist = 0;
	dist = v_oper(SUB, ray->origin, sphere->origin);
	if (!_get_sphere_hit(ray, sphere, dist, &hit_dist))
		return (0);
	return (_check_nearest_sphere_hit(ray, sphere, hit_dist));
}


// t_coords			get_hit_points(t_ray ray)
// {
// 	return (v_oper(ADD, ray.origin, v_scale(ray.dir, ray.dist)));
// }

// static void		bhaskara(double a, double b, double c, double *res)
// {
// 	double		sqrt_discriminant;
// 	double		aux[2];

// 	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
// 	aux[0] = (-b - sqrt_discriminant) / (2 * a);
// 	aux[1] = (-b + sqrt_discriminant) / (2 * a);
// 	if (aux[0] < aux[1])
// 	{
// 		res[0] = aux[0];
// 		res[1] = aux[1];
// 	}
// 	else
// 	{
// 		res[0] = aux[1];
// 		res[1] = aux[0];
// 	}
// }

// int intersect_sphere(t_ray *ray, t_object *sphere)
// {
// 	t_coords		v_sp2ray;
// 	double		time[2];

// 	v_sp2ray = v_oper(SUB, ray->origin, sphere->origin);
// 	bhaskara(v_square(ray->dir), 2 * v_dot(ray->dir, v_sp2ray),
// 				v_dot(v_sp2ray, v_sp2ray) - pow(sphere->diameter / 2, 2), time);
// 	if (ray->dist > time[0] && time[0] > 0)
// 	{
// 		ray->dist = time[0];
// 		ray->hit = get_hit_points(*ray);
// 		ray->hit_norm = v_norm(v_oper(SUB, ray->hit, sphere->origin));
// 		ray->color = sphere->color;
// 		return (true);
// 	}
// 	return (false);
// }