/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:11:35 by ccrottie          #+#    #+#             */
/*   Updated: 2023/10/02 16:11:36 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function checks the two solutions by using "dist" variables, calculated
	before. If the condition is valid, that means both our solutions are valid :
	we take the smaller solution (the closest hit). Else, we take the only valid
	solution.
*/

static void	_check_side_solutions(t_object *cyl, double solutions[2], double dist[2])
{
	if ((dist[0] >= 0 && dist[0] <= cyl->height && solutions[0] > EPSILON) && \
		(dist[1] >= 0 && dist[1] <= cyl->height && solutions[1] > EPSILON))
	{
		if (solutions[0] > solutions[1])
			solutions[0] = solutions[1];
	}
	else if (dist[1] >= 0 && dist[1] <= cyl->height && solutions[1] > EPSILON)
		solutions[0] = solutions[1];
}

/*
	This function calculates the potential position of the hit on the side
	of the cylinder. It uses the cylinder equation, a quadratic equation
	that can have zero, one or two solutions.
	If delta is less than 0, our ray does not intersect with the cylinder.
	If delta is equal to 0, our ray is tangent to the cylinder.
	If delta is more than 0, our ray intersect and goes through the cylinder.
	That means we have two solutions.
*/

static int	_cylinder_equation(t_object *cyl, \
	t_coords vectors[2], double solutions[2])
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = v_dot(vectors[0], vectors[0]);
	b = 2 * v_dot(vectors[0], vectors[1]);
	c = v_dot(vectors[1], vectors[1]) - pow(cyl->diameter, 2);
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	solutions[0] = (-b + sqrtf(delta)) / (2 * a);
	solutions[1] = (-b - sqrtf(delta)) / (2 * a);
	if (solutions[0] < EPSILON && solutions[1] < EPSILON)
		return (0);
	return (1);
}

static void	_get_cylinder_vectors(t_ray *ray, t_object *cyl, \
	t_coords vectors[2])
{
	t_coords	ray2cyl;

	ray2cyl = v_oper(SUB, ray->origin, cyl->origin);
	vectors[0] = v_scale(MULT, cyl->dir, v_dot(ray->dir, cyl->dir));
	vectors[0] = v_oper(SUB, ray->dir, vectors[0]);
	vectors[1] = v_scale(MULT, cyl->dir, v_dot(ray2cyl, cyl->dir));
	vectors[1] = v_oper(SUB, ray2cyl, vectors[1]);
}

/*
	This function calculates the potential position of the hit on the side
	of the cylinder. It calculates the cylinder vectors, used as arguments
	for the cylinder equation. The solution(s) of this equation, if there
	exist any, are then checked to know which one to use and display.
*/

double	get_side_hit(t_ray *ray, t_object *cyl)
{
	double		solutions[2];
	double		dist[2];
	t_coords	vectors[2];
	t_coords	cyl2ray;

	_get_cylinder_vectors(ray, cyl, vectors);
	if (!_cylinder_equation(cyl, vectors, solutions))
		return (INFINITY);
	cyl2ray = v_oper(SUB, cyl->origin, ray->origin);
	dist[0] = v_dot(cyl->dir, \
		v_oper(SUB, v_scale(MULT, ray->dir, solutions[0]), cyl2ray));
	dist[1] = v_dot(cyl->dir, \
		v_oper(SUB, v_scale(MULT, ray->dir, solutions[1]), cyl2ray));
	if (!((dist[0] >= 0 && dist[0] <= cyl->height && solutions[0] > EPSILON) || \
		(dist[1] >= 0 && dist[1] <= cyl->height && solutions[1] > EPSILON)))
		return (INFINITY);
	_check_side_solutions(cyl, solutions, dist);
	return (solutions[0]);
}
