/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:49 by colas             #+#    #+#             */
/*   Updated: 2023/08/30 17:36:18 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	v_dist(t_coords v, t_coords u)
{
	return (sqrtf(pow(u.x - v.x, 2) + \
		pow(u.y - v.y, 2) + pow(u.z - v.z, 2)));
}

t_coords	v_norm(t_coords v)
{
	double	v_len;

	v_len = sqrtf(v_dot(v, v));
	if (v_len == 0)
		v_len = 0.000001;
	return (v_scale(MULT, v, 1 / v_len));
}

t_coords	v_scale(t_scale mode, t_coords v, double scale)
{
	if (mode == MULT)
		return ((t_coords){v.x * scale, v.y * scale, v.z * scale});
	return ((t_coords){v.x / scale, v.y / scale, v.z / scale});
}

double	v_dot(t_coords v, t_coords u)
{
	return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
}

t_coords	v_oper(t_oper mode, t_coords v, t_coords u)
{
	if (mode == ADD)
		return ((t_coords){(v.x + u.x), (v.y + u.y), (v.z + u.z)});
	else if (mode == SUB)
		return ((t_coords){(v.x - u.x), (v.y - u.y), (v.z - u.z)});
	else
		return ((t_coords){(v.y * u.z) - (v.z * u.y),
			(v.z * u.x) - (v.x * u.z),
			(v.x * u.y) - (v.y * u.x)});
}
