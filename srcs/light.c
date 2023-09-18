/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:51:23 by cgelin            #+#    #+#             */
/*   Updated: 2023/09/18 11:56:14 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_shadow(t_data *data, t_ray *ray)
{
	t_ray	shadow;

	shadow.origin = v_oper(ADD, ray->hit, v_scale(ray->hit_norm, 0.0000001));
	shadow.dir = v_norm(v_oper(SUB, data->light.origin, shadow.origin));
	return (find_intersect(data, &shadow));
}

static int	_add_light(t_light *light, t_ray *ray)
{
	t_coords	light_normal;
	float		gain;
	float		r2;
	float		light_bright;

	light_normal = v_oper(SUB, light->origin, ray->hit);
	r2 = v_square(light_normal);
	gain = v_dot(v_norm(light_normal), ray->hit_norm);
	if (gain <= 0)
		light_bright = 0;
	else
		light_bright = (light->intensity * gain * 1000) / (4.0 * M_PI * r2);
	return (color_product(color_add(10, color_scale(ray->color.hex, light_bright)), 0xFFFFFF));
}

int	get_ray_color(t_data *data, t_ray *ray)
{
	int		ambient;
	int		color;
	int		shadow;

	if (!find_intersect(data, ray))
		return (0);
	ambient = color_scale(data->ambient.color.hex, data->ambient.intensity);
	color = color_product(ray->color.hex, ambient);
	shadow = !_check_shadow(data, ray);
	color = color_add(color, shadow * _add_light(&data->light, ray));
	return (color);
}