/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:15:08 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/06 14:57:22 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coords	get_hit_point(t_ray *ray)
{
	return (v_oper(ray->origin, v_scale(ray->dir, ray->dist), ADD));
}

int	check_nearest_sphere_hit(t_ray *ray, t_object *sphere, double hit_dist)
{
	if (ray->dist > hit_dist)
	{
		ray->dist = hit_dist;
		ray->hit = get_hit_point(ray);
		ray->hit_norm = v_norm(v_oper(ray->hit, sphere->coords, SUB));
		ray->color = sphere->color;
		return (1);
	}
	return (0);
}

int	get_sphere_hit(t_ray *ray, t_object *sphere, t_coords dist, double *res)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	a = v_square(ray->dir);
	b = 2 * v_dot(ray->dir, dist);
	c = v_dot(dist, dist) - \
		((sphere->diameter / 2) * (sphere->diameter / 2));
	delta = (b * b) - (4 * a * c);
	if (delta < 0)
		return (0);
	*res = (-b - sqrt(delta)) / (2 * a);
	return (1);
}

int	intersect_sphere(t_ray *ray, t_object *sphere)
{
	t_coords	dist;
	double		hit_dist;

	hit_dist = 0;
	dist = v_oper(ray->origin, sphere->coords, SUB);
	if (!get_sphere_hit(ray, sphere, dist, &hit_dist))
		return (0);
	return (check_nearest_sphere_hit(ray, sphere, hit_dist));
}

int	find_intersect(t_data *data, t_ray *ray)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	ray->dist = INFINITY;
	while (i < data->obj_nbr + 1)
	{
		if (data->objects[i].type == SPHERE)
			ret += intersect_sphere(ray, &data->objects[i]);
		// else if (data->objects[i].type == PLANE)
		// 	ret += intersect_plane(data, ray, &data->objects[i]);
		// else
		// 	ret += intersect_cylinder(data, ray, &data->objects[i]);
		i++;
	}
	return (ret);
}

int	color_product(int color1, int color2)
{
	t_color	temp;

	temp.r = (((float)(color1 >> 0x10) / 0xFF) * \
			((float)(color2 >> 0x10) / 0xFF)) * 0xFF;
	temp.g = (((float)((color1 >> 0x08) & 0xFF) / 0xFF) * \
			((float)((color2 >> 0x08) & 0xFF) / 0xFF)) * 0xFF;
	temp.b = (((float)(color1 & 0xFF) / 0xFF) * \
			((float)(color2 & 0xFF) / 0xFF)) * 0xFF;
	return ((temp.r << 0x10) | (temp.g << 0x08) | temp.b);
}

int	color_scale(int color, double intensity)
{
	t_color	temp;

	temp.r = (color >> 0x10) * intensity;
	temp.g = ((color >> 0x08) & 0xFF) * intensity;
	temp.b = (color & 0xFF) * intensity;
	return ((temp.r << 0x10) | (temp.g << 0x08) | temp.b);
}

int	get_ray_color(t_data *data, t_ray *ray)
{
	int	ambient;
	int	color;

	if (!find_intersect(data, ray))
		return (0);
	ambient = color_scale(data->ambient.color.hex, data->ambient.intensity);
	color = color_product(ray->color.hex, ambient);
	// add_light
	return (color);
}

/* This fonction creates a Ray that follows the camera direction.

1 - Ajusting the ray direction taking count of the screen pixel position.
2 - Adding the low left corner to the ray to fit our matrice.
3 - Substracting the ray direction by the ray origin so the origin of the ray is
	camera relative then normalising it to make it simpler for calculations.
*/
t_ray	create_ray(t_cam cam, double x, double y) 
{
	t_ray ray;

	ray.origin = cam.origin;
	ray.dir = v_oper(v_scale(cam.hor_fov, x), v_scale(cam.ver_fov, y), ADD);
	// printf("x = %f y = %f z = %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
	ray.dir = v_oper(ray.dir, cam.ll_corner, ADD);
	ray.dir = v_norm(v_oper(ray.dir, ray.origin, SUB));
	return (ray);
}
