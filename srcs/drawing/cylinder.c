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

static int	_check_nearest_cylinder_hit(t_ray *ray, t_object *cy, \
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
		ray->color = cy->color;
	}
	return (in_cy[0] || in_cy[1]);
}

static void	_check_cylinder_solutions(t_ray *ray, t_object *cy, \
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
}

static void	_cylinder_equation(t_coords vectors[2], \
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
}

static void	_get_cylinder_vectors(t_coords *vectors, t_ray *ray, t_object *cy)
{
	vectors[0] = v_scale(cy->dir, v_dot(ray->dir, cy->dir));
	vectors[0] = v_oper(SUB, ray->dir, vectors[0]);
	vectors[1] = v_oper(SUB, ray->origin, cy->origin);
	vectors[1] = v_scale(cy->dir, v_dot(vectors[1], cy->dir));
	vectors[1] = v_oper(SUB, v_oper(SUB, ray->origin, cy->origin), vectors[1]);
}

int	intersect_cylinder(t_ray *ray, t_object *cy)
{
	t_coords	vectors[2];
	double		solutions[2];
	bool		in_cy[2];

	_get_cylinder_vectors(vectors, ray, cy);
	_cylinder_equation(vectors, cy, solutions);
	_check_cylinder_solutions(ray, cy, solutions, in_cy);
	return (_check_nearest_cylinder_hit(ray, cy, solutions, in_cy));
}
