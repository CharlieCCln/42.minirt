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

/*
	This function checks if our new distance to the hit is smaller than the
	previous distance. If that's the case, that means this cylinder is closer
	than the previous object we would show, so we get the color and distance
	of this cylinder to display it later. We also calculate the normal of the
	hit, that will help us later with the lights. Depending on our ray going
	through curved area only or through one or more "caps", we use two ways
	to calculate this hit normal.
*/

/* static int	_check_nearest_cylinder_hit(t_ray *ray, t_object *cy, \
	double solutions[2], bool in_cy[2])
{
	if ((in_cy[0] || in_cy[1]) && ray->dist > solutions[0] && \
		solutions[0] > EPSILON)
	{
		ray->dist = solutions[0];
		ray->hit = get_hit_point(ray);
		if (in_cy[0] == false && in_cy[1] == true)
			ray->hit_norm = v_scale(ray->hit_norm, -1);
		else
			ray->hit_norm = v_norm(v_oper(SUB, ray->hit, \
				v_oper(ADD, v_scale(cy->dir, solutions[1]), cy->origin)));
		if (v_dot(ray->dir, ray->hit_norm) > 0)
			ray->hit_norm = v_scale(ray->hit_norm, -1);
		ray->color = cy->color;
	}
	return (in_cy[0] || in_cy[1]);
} */

/*
	This function checks how our ray intersects with the cylinder.
	It first calculates the cylinder-origin-to-ray-origin vector.
	It uses this vector to calculate the two distances between the
	cylinder origin and the intersection points.
	Using these distances and comparing them to the height of the cylinder,
	we can know if the ray goes through the curved area of the cylinder
	only, or if it also goes through a "cap" (top or bottom part).
	Depending on this, we will keep only one solution to the equation,
	and replace the other one with the origin-to-hit distance value.
*/

/* static void	_check_cylinder_solutions(t_ray *ray, t_object *cy, \
	double solutions[2], bool in_cy[2])
{
	t_coords	cyl2ray;
	double		ori2inter[2];

	cyl2ray = v_oper(SUB, cy->origin, ray->origin);
	ori2inter[0] = v_dot(cy->dir, v_oper(SUB, \
		v_scale(ray->dir, solutions[0]), cyl2ray));
	ori2inter[1] = v_dot(cy->dir, v_oper(SUB, \
		v_scale(ray->dir, solutions[1]), cyl2ray));
	in_cy[0] = (ori2inter[0] >= 0 && ori2inter[0] <= cy->height && \
		solutions[0] > EPSILON);
	in_cy[1] = (ori2inter[1] >= 0 && ori2inter[1] <= cy->height && \
		solutions[1] > EPSILON);
	if (in_cy[0] == false && in_cy[1] == true)
	{
		solutions[0] = solutions[1];
		solutions[1] = ori2inter[1];
	}
	else
		solutions[1] = ori2inter[0];
	if (in_cy[0] == true && solutions[0] <= EPSILON)
		in_cy[0] = false;
	if (in_cy[1] == true && solutions[1] <= EPSILON)
		in_cy[1] = false;
} */

/*
	This function calculates the potential position of the hit on the cylinder.
	It uses the Ray-Cylinder equation, a quadratic equation that can have zero,
	one or two solutions.
	If delta is less than 0, our ray does not intersect with the cylinder.
	If delta is equal to 0, our ray is tangent to the cylinder.
	If delta is more than 0, our ray intersect and goes through the cylinder.
	Unlike the sphere, if there is two solutions, we will need to keep both,
	in order to know how our ray intersects the cylinder.
*/

/* static void	_cylinder_equation(t_coords vectors[2], \
	t_object *cy, double solutions[2])
{
	double		a;
	double		b;
	double		c;
	double		delta;

	a = v_square(vectors[0]);
	b = 2 * v_dot(vectors[0], vectors[1]);
	c = v_square(vectors[1]) - (cy->diameter / 2) * (cy->diameter / 2);
	delta = (b * b) - (4 * a * c);
	solutions[0] = (-b - sqrt(delta)) / (2 * a);
	solutions[1] = (-b + sqrt(delta)) / (2 * a);
} */

/*
	This function calculates two vectors, that we will need to use to get the
	potential position of the intersection.
	-	vectors[0] will help us to know if our ray intersect with the curved
		surface of the cylinder,
	-	and vectors[1] will help us to know if our ray intersect with the
		top and bottom "caps" of the cylinder.
*/

/* static void	_get_cylinder_vectors(t_coords *vectors, t_ray *ray, t_object *cy)
{
	vectors[0] = v_scale(cy->dir, v_dot(ray->dir, cy->dir));
	vectors[0] = v_oper(SUB, ray->dir, vectors[0]);
	vectors[1] = v_oper(SUB, ray->origin, cy->origin);
	vectors[1] = v_scale(cy->dir, v_dot(vectors[1], cy->dir));
	vectors[1] = v_oper(SUB, v_oper(SUB, ray->origin, cy->origin), vectors[1]);
} */

/*
	This function tends to find if our ray intersects with a given cylinder.
	To do this, it first gets the calculates the potential coords of the hits.
	Then, if there is one or more hit(s), checks on what part of the
	cylinder the hits are. Finally, it checks if the hit is visible
	or behind another object.
*/

/* int	intersect_cylinder(t_ray *ray, t_object *cy)
{
	t_coords	vectors[2];
	double		solutions[2];
	bool		in_cy[2];

	_get_cylinder_vectors(vectors, ray, cy);
	_cylinder_equation(vectors, cy, solutions);
	_check_cylinder_solutions(ray, cy, solutions, in_cy);
	return (_check_nearest_cylinder_hit(ray, cy, solutions, in_cy));
} */

static bool	within_cylinder_radius(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + ray->dir.x * t;
	z = ray->origin.z + ray->dir.z * t;
	if ((x * x + z * z) <= 1)
		return (true);
	return (false);
}

static bool	check_cylinder_caps(t_ray *ray, t_object *cy)
{
	bool	intersected;
	double	t;

	intersected = false;
	if (fabs(ray->dir.y) > EPSILON)
	{
		t = (-(cy->height / 2) - ray->origin.y) / ray->dir.y;
		if (within_cylinder_radius(ray, t) && ray->dist > t)
		{
			ray->dist = t;
			ray->color = cy->color;
			ray->hit = get_hit_point(ray);
			intersected = true;
		}
		t = ((cy->height / 2) - ray->origin.y) / ray->dir.y;
		if (within_cylinder_radius(ray, t) && ray->dist > t)
		{
			ray->dist = t;
			ray->color = cy->color;
			ray->hit = get_hit_point(ray);
			intersected = true;
		}
	}
	return (intersected);
}

static bool	add_cylinder_intersections(t_ray *ray,
		t_object *cy, double *ts)
{
	double	y0;
	double	y1;
	bool	intersected;

	intersected = false;
	if (ts[0] > ts[1])
	{
		y0 = ts[0];
		ts[0] = ts[1];
		ts[1] = y0;
	}
	y0 = ray->origin.y + ts[0] * ray->dir.y;
	if (y0 > (-cy->height / 2) && y0 < (cy->height / 2) && ray->dist > ts[0])
	{
		ray->dist = ts[0];
		ray->color = cy->color;
		ray->hit = get_hit_point(ray);
		intersected = true;
	}
	y1 = ray->origin.y + ts[1] * ray->dir.y;
	if (y1 > (-cy->height / 2) && y1 < (cy->height / 2) && ray->dist > ts[1])
	{
		ray->dist = ts[1];
		ray->color = cy->color;
		ray->hit = get_hit_point(ray);
		intersected = true;
	}
	return (intersected);
}

int	intersect_cylinder(t_ray *ray, t_object *cylinder)
{
	bool	intersected;
	double	a;
	double	b;
	double	ts[2];
	double	discriminant;

	intersected = check_cylinder_caps(ray, cylinder);
	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	if (fabs(a) < EPSILON)
		return (intersected);
	b = 2 * ray->dir.x * ray->origin.x + 2 * ray->dir.z * ray->origin.z;
	discriminant = b * b - 4 * a * \
		(ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1);
	if (discriminant < 0)
		return (intersected);
	a *= 2;
	b *= -1;
	discriminant = sqrt(discriminant);
	ts[0] = (b - discriminant) / (a);
	ts[1] = (b + discriminant) / (a);
	if (add_cylinder_intersections(ray, cylinder, ts))
		intersected = true;
	return (intersected);
}