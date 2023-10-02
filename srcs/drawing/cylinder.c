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

double	solve_plane(t_coords o, t_coords d, t_coords plane_p, t_coords plane_nv)
{
	double	x;
	double	denom;

	denom = v_dot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (v_dot(plane_nv, v_oper(SUB, plane_p, o))) / denom;
	if (x > EPSILON)
		return (x);
	else
		return (INFINITY);
}

double	distance(const t_coords p1, const t_coords p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + \
	pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

static double	caps_intersection(t_ray ray, const t_object cyl)
{
	double		id1;
	double		id2;
	t_coords	ip1;
	t_coords	ip2;
	t_coords	c2;

	c2 = v_oper(ADD, cyl.origin, v_scale(cyl.dir, cyl.height));
	id1 = solve_plane(ray.origin, ray.dir, cyl.origin, cyl.dir);
	id2 = solve_plane(ray.origin, ray.dir, c2, cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = v_oper(ADD, ray.origin, v_scale(ray.dir, id1));
		ip2 = v_oper(ADD, ray.origin, v_scale(ray.dir, id2));
		if ((id1 < INFINITY && distance(ip1, cyl.origin) <= cyl.diameter) \
		&& (id2 < INFINITY && distance(ip2, c2) <= cyl.diameter))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY && \
		distance(ip1, cyl.origin) <= cyl.diameter)
			return (id1);
		else if (id2 < INFINITY && distance(ip2, c2) <= cyl.diameter)
			return (id2);
	}
	return (INFINITY);
}

static bool	solve_cylinder(double x[2], t_ray ray, const t_object cylinder)
{
	t_coords	v;
	t_coords	u;
	double		a;
	double		b;
	double		c;

	v = v_scale(cylinder.dir, v_dot(ray.dir, cylinder.dir));
	v = v_oper(SUB, ray.dir, v);
	u = v_scale(cylinder.dir, v_dot(\
	v_oper(SUB, ray.origin, cylinder.origin), cylinder.dir));
	u = v_oper(SUB, v_oper(SUB, ray.origin, cylinder.origin), u);
	a = v_dot(v, v);
	b = 2 * v_dot(v, u);
	c = v_dot(u, u) - pow(cylinder.diameter, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (x[0] < EPSILON && x[1] < EPSILON)
		return (0);
	return (1);
}

static void		calc_cy_normal(double x2[2], t_object cylinder, double dist1, double dist2)
{
	double	dist;
	double	x;

	if ((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) \
	&& (dist2 >= 0 && dist2 <= cylinder.height && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? dist1 : dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON)
	{
		dist = dist1;
		x = x2[0];
	}
	else
	{
		dist = dist2;
		x = x2[1];
	}
	x2[0] = x;
}

static double	cy_intersection(t_ray ray, t_object cylinder)
{
	double	x2[2];

	if (!solve_cylinder(x2, ray, cylinder))
		return (INFINITY);
	double dist1 = v_dot(cylinder.dir, v_oper(SUB, \
	v_scale(ray.dir, x2[0]), v_oper(SUB, cylinder.origin, ray.origin)));
	double dist2 = v_dot(cylinder.dir, v_oper(SUB, \
	v_scale(ray.dir, x2[1]), v_oper(SUB, cylinder.origin, ray.origin)));
	if (!((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) \
	|| (dist2 >= 0 && dist2 <= cylinder.height && x2[0] > EPSILON)))
		return (INFINITY);
	calc_cy_normal(x2, cylinder, dist1, dist2);
	return (x2[0]);
}

double	cylinder_intersection(const t_ray ray, const t_object cylinder, bool *is_on_side)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = cy_intersection(ray, cylinder);
	caps_inter = caps_intersection(ray, cylinder);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			*is_on_side = true;
			return (cylinder_inter);
		}
		return (caps_inter);
	}
	return (INFINITY);
}

t_coords get_closest_point_from_line(t_coords A, t_coords B, t_coords P)
{
	t_coords AP = v_oper(SUB, P, A);
	t_coords AB = v_oper(SUB, B, A);
	double ab2 = v_dot(AB, AB);
	double ap_ab = v_dot(AP, AB);
	double t = ap_ab / ab2;
	if (t < 0.0)
		t = 0.0;
	else if (t > 1.0)
		t = 1.0;
	return (v_oper(ADD, A, v_scale(AB, t)));
}

int	intersect_cylinder(t_ray *ray, t_object *cyl)
{
	double		hit_dist;
	bool		is_on_side;
	t_coords	pos;

	is_on_side = false;
	hit_dist = cylinder_intersection(*ray, *cyl, &is_on_side);
	if (ray->dist > hit_dist && hit_dist > EPSILON)
	{
		double length = distance((t_coords){0,0,0}, cyl->dir);
		cyl->dir = (t_coords){cyl->dir.x / length, cyl->dir.y / length, cyl->dir.z / length};
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		pos = v_oper(ADD, cyl->origin, v_scale(cyl->dir, cyl->height));
		if (is_on_side)
			ray->hit_norm = v_oper(SUB, \
			get_closest_point_from_line(cyl->origin, pos, ray->hit), ray->hit);
		else
			ray->hit_norm = cyl->dir;
		if (v_dot(ray->dir, ray->hit_norm) > 0)
			ray->hit_norm = v_scale(ray->hit_norm, -1);
		ray->hit_norm = v_norm(ray->hit_norm);
		ray->color = cyl->color;
		return (1);
	}
	return (0);
}