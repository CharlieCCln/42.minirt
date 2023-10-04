/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelin <cgelin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:51:23 by cgelin            #+#    #+#             */
/*   Updated: 2023/10/03 10:35:29 by cgelin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function checks if we have to render a shadow at the given point.
	The shadow will be a ray that has for origin the hit slightly offset to
	avoid self-intersection.
	The direction of the ray bounced is determined by substracting
	the origin of the light with our previous calculated origin of shadow.
	Then we check if our shadow ray hits an object with find_intersect 
	previously used for rendering objects.
*/

int check_shadow(t_data *data, t_ray *ray)
{
    t_ray	shadow;

	shadow.origin = v_oper(ADD, data->light.origin, v_scale(MULT, ray->hit_norm, EPSILON));
	shadow.dir = v_norm(v_oper(SUB, ray->hit, shadow.origin));
	find_intersect(data, &shadow);
	if (v_dist(data->light.origin, ray->hit) < shadow.dist)
		return (1);
	return (0);
}

/*
	This function calculates the light at a point on an object and returns it.
	We get the vector that goes from the light to the hit point, squaring it. 
	It now represents the distance between the light and the object.
	Gain is the amount of light hitting the hit point.
	if the gain is non zero or negative, we calculate 
	the light bright based on the previous values and a constant, 
	the calculation is relative to the natural circular expansion 
	of the light represented by 4.0 * M_PI * r2.
	Then we can calculate our final light by multypling the hit color with the
	light, adding a constant to get a minimum light brightness and multiplying
	it by white to get a maximum light brightness.
*/

int	add_light(t_data *data, t_ray *ray)
{
	t_coords	light_normal;
	double		gain;
	double		r2;
	double		light_bright;

	
	light_normal = v_oper(SUB, data->light.origin, ray->hit);
	r2 = v_dot(light_normal, light_normal);
	gain = v_dot(v_norm(light_normal), ray->hit_norm);
	if (gain <= 0)
		light_bright = 0;
	else
		light_bright = (data->light.intensity * gain * 500) / (4.0 * M_PI * r2);
	return (color_product(color_add(10, \
		color_scale(ray->color.hex, light_bright)), 0xFFFFFF));
}
