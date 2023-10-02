/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:34:48 by ccrottie          #+#    #+#             */
/*   Updated: 2023/10/02 11:34:49 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function checks the two solutions by using "dist" variables, calculated
	before. If both viable[0] and viable[1] are valid, that means both our 
	solutions are valid : we take the smaller solution (the closest hit). 
	Else, we take the only valid solution. If there is no valid solution, that
	means the ray doesn't go through any of the caps.
*/

static double	_check_caps_solutions(t_object *cyl, t_coords dist[2], \
	t_coords cyl_top, double solutions[2])
{
	bool	viable[2];

	viable[0] = (solutions[0] < INFINITY && \
		v_dist(dist[0], cyl->origin) <= cyl->diameter);
	viable[1] = (solutions[1] < INFINITY && \
		v_dist(dist[1], cyl_top) <= cyl->diameter);
	if (viable[0] && viable[1])
	{
		if (solutions[0] < solutions[1])
			return (solutions[0]);
		return (solutions[1]);
	}
	else if (viable[0])
		return (solutions[0]);
	else if (viable[1])
		return (solutions[1]);
	return (INFINITY);
}

/*
	Firstly we check if the ray is parallel to the caps by checking 
	the dot product of the direction of the ray and the caps. 
	Then we calculate the hit distance from the camera and return
	the solution.
*/

static double	_caps_equation(t_ray *ray, t_coords origin, t_coords cyl_dir)
{
	double	solution;
	double	dot;

	dot = v_dot(cyl_dir, ray->dir);
	if (!dot)
		return (INFINITY);
	solution = (v_dot(cyl_dir, v_oper(SUB, origin, ray->origin))) / dot;
	if (solution > EPSILON)
		return (solution);
	return (INFINITY);
}

/*
	This function calculates the potential position of the hit on the caps
	of the cylinder. The solution(s) of the equation, if there
	exist any, are then checked to know which one to use and display.
*/

double get_caps_hit(t_ray *ray, t_object *cyl)
{
	t_coords	cyl_top;
	t_coords	dist[2];
	double		solutions[2];

	cyl_top = v_oper(ADD, cyl->origin, v_scale(MULT, cyl->dir, cyl->height));
	solutions[0] = _caps_equation(ray, cyl->origin, cyl->dir);
	solutions[1] = _caps_equation(ray, cyl_top, cyl->dir);
	if (solutions[0] < INFINITY || solutions[1] < INFINITY)
	{
		dist[0] = v_oper(ADD, ray->origin, \
			v_scale(MULT, ray->dir, solutions[0]));
		dist[1] = v_oper(ADD, ray->origin, \
			v_scale(MULT, ray->dir, solutions[1]));
		return (_check_caps_solutions(cyl, dist, cyl_top, solutions));
	}
	return (INFINITY);
}
