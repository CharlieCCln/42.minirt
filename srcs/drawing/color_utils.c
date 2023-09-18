/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:37:12 by colas             #+#    #+#             */
/*   Updated: 2023/09/18 11:53:39 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_rgb(int nbr)
{
	if (nbr > 0xFF)
		return (0xFF);
	else if (nbr < 0)
		return (0);
	else
		return (nbr);
}

/*
	This function multiplies color of the object by ambient light
	to get the final color.
	Each resulting component(r, g, b) is calculated by isolating each component of 
	color1 from the 2 others, normalising it by dividing it by 255, 
	multiplying it by the same component (normalised) in color2 and then
	de-normalising the result by multiplying it by 255.
*/

int	color_product(int color1, int color2)
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

int	color_scale(int color, double intensity)
{
	t_color	temp;

	temp.r = _check_rgb((color >> 16) * intensity);
	temp.g = _check_rgb(((color >> 8) & 255) * intensity);
	temp.b = _check_rgb((color & 255) * intensity);
	return ((temp.r << 16) | (temp.g << 8) | temp.b);
}

int	color_add(int c1, int c2)
{
	t_color	temp;

	temp.r = _check_rgb((c1 >> 16) + (c2 >> 16));
	temp.g = _check_rgb((c1 >> 8 & 255) + (c2 >> 8 & 255));
	temp.b = _check_rgb((c1 & 255) + (c2 & 255));
	return ((temp.r << 16) | (temp.g << 8) | temp.b);
}
