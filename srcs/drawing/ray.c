/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/21 12:58:17 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function is used during the calculation of the 3 types of objects,
	it adds to the ray origin the length of the ray times its direction, this
	gets the point where the objects is hit by the ray. 
*/

t_coords	get_hit_point(t_ray *ray)
{
	return (v_oper(ADD, ray->origin, v_scale(ray->dir, ray->dist)));
}

/*
	For each item, we are going to calculate the rays that hits them
	by calling the appropriate function. If nothing is hit,
	the function returns 0.
*/

int	find_intersect(t_data *data, t_ray *ray, int mode)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ray->dist = INFINITY;
	while (i < data->obj_nbr + 1)
	{
		if (data->objects[i].type == SPHERE)
			ret += intersect_sphere(ray, &data->objects[i], mode);
		else if (data->objects[i].type == PLANE)
			ret += intersect_plane(ray, &data->objects[i], mode);
		else
			ret += intersect_cylinder(ray, &data->objects[i]);
		if (ray->inside && !data->cam.inside)
			data->cam.inside = 1;
		i++;
	}
	// if (mode)
	// 	printf("%f / %f / %f : %f, %f, %f\n", ray->hit_norm.x, ray->hit_norm.y, ray->hit_norm.z, ray->hit.x, ray->hit.y, ray->hit.z);
	if (ret)
		return (1);
	return (0);
}

/* This fonction creates a Ray that follows the camera direction.

1 - Ajusting the ray direction taking count of the screen pixel position.
2 - Adding the low left corner to the ray to fit our matrice.
3 - Substracting the ray direction by the ray origin so the origin of the ray is
	camera relative then normalising it to make it simpler for calculations.
*/

t_ray	create_ray(t_cam cam, double x, double y)
{
	t_ray	ray;

	ray.origin = cam.origin;
	ray.dir = v_oper(ADD, v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y));
	ray.dir = v_oper(ADD, ray.dir, cam.ll_corner);
	ray.dir = v_norm(v_oper(SUB, ray.dir, ray.origin));
	ray.inside = 0;
	return (ray);
}
