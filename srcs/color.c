/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:37:12 by colas             #+#    #+#             */
/*   Updated: 2023/09/13 09:59:03 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function multiplies color of the object by ambient light to get the final color.
	Each resulting component(r, g, b) is calculated by isolating each component of 
	color1 from the 2 others, normalising it by dividing it by 255, 
	multiplying it by the same component (normalised) in color2 and then
	de-normalising the result by multiplying it by 255.
*/

static int	_color_product(int color1, int color2)
{
	t_color	temp;

	temp.r = (((float)(color1 >> 16) / 255) * \
			((float)(color2 >> 16) / 255)) * 255;
	temp.g = (((float)((color1 >> 8) & 255) / 255) * \
			((float)((color2 >> 8) & 255) / 255)) * 255;
	temp.b = (((float)(color1 & 255) / 255) * \
			((float)(color2 & 255) / 255)) * 255;
	return ((temp.r << 16) | (temp.g << 8) | temp.b);
}

/*
	This function multiplies ambient light intensity by each component.
	The operators ">> 16", ">> 8" and "& 255" are known for isolating each 
	rgb components in bits to apply the multiplication to each component 
	before regrouping them to create the resulting color.
*/

static int	_color_scale(int color, double intensity)
{
	t_color	temp;

	temp.r = (color >> 16) * intensity;
	temp.g = ((color >> 8) & 255) * intensity;
	temp.b = (color & 255) * intensity;
	return ((temp.r << 16) | (temp.g << 8) | temp.b);
}

int	check_shadow(t_data *data, t_ray *ray)
{
	t_ray	shadow;

	shadow.origin = v_oper(ADD, ray->hit, v_scale(ray->hit_norm, 0.0000001));
	shadow.dir = v_norm(v_oper(SUB, data->light.origin, shadow.origin));
	return (find_intersect(data, &shadow));
}

int	add_light(t_light *light, t_ray *ray)
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
	return (_color_product(_color_scale(ray->color.hex, light_bright), 0xFFFFFF));
}

int			color_add(int c1, int c2)
{
	int		r;
	int		g;
	int		b;

	r = (c1 >> 16) + (c2 >> 16);
	g = (c1 >> 8 & 255) + (c2 >> 8 & 255);
	b = (c1 & 255) + (c2 & 255);
	return ((r << 16) | (g << 8) | b);
}

int	get_ray_color(t_data *data, t_ray *ray)
{
	int		ambient;
	int		color;
	int		shadow;

	if (!find_intersect(data, ray))
		return (0);
	ambient = _color_scale(data->ambient.color.hex, data->ambient.intensity);
	color = _color_product(ray->color.hex, ambient);
	shadow = !check_shadow(data, ray);
	color = color_add(color, shadow * add_light(&data->light, ray));
	return (color);
}