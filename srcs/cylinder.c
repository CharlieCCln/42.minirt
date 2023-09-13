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

int	_check_nearest_cyl_hit(t_ray *ray, t_object *cylinder, double hit_dist, double y)
{
	if (ray->dist > hit_dist)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(ray->hit, \
			v_oper(v_scale(cylinder->dir, y), cylinder->origin, SUB), SUB));
		ray->color = cylinder->color;
		return (1);
	}
	return (0);
}

int			hit_cy(t_ray *ray, t_object *cylinder)
{
	t_coords	dist;
	t_coords	v_cyl2ray;
	double		hit_dist;
	double		y;
	t_coords v[2];

	dist = v_oper(ray->origin, cylinder->origin, SUB);
	v[0] = v_oper(ray->dir, v_scale(cylinder->dir, v_dot(ray->dir, cylinder->dir)), SUB);
	v[1] = v_oper(v_oper(ray->origin, cylinder->origin, SUB),
			v_scale(cylinder->dir, v_dot(v_oper(ray->origin, cylinder->origin, SUB), cylinder->dir)), SUB);
	bhaskara(v_len_sqr(v[0]), 2 * v_dot(v[0], v[1]),
			 v_len_sqr(v[1]) - (cylinder->diameter / 2) * (cylinder->diameter / 2), &hit_dist);
	v_cyl2ray = v_oper(cylinder->origin, ray->origin, SUB);
	y = v_dot(cylinder->dir, v_oper(v_scale(ray->dir, hit_dist), v_cyl2ray, SUB));
	return (_check_nearest_cyl_hit(ray, cylinder, hit_dist, y));
}
