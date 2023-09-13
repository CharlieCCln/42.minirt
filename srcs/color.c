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

int	get_ray_color(t_data *data, t_ray *ray)
{
	int	ambient;
	int	color;

	if (!find_intersect(data, ray))
		return (0);
	ambient = _color_scale(data->ambient.color.hex, data->ambient.intensity);
	color = _color_product(ray->color.hex, ambient);
	// add_light
	return (color);
}