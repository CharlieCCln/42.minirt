/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: colas <colas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:07:49 by colas             #+#    #+#             */
/*   Updated: 2023/08/30 15:08:28 by colas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coords		v_norm(t_coords v)
{
	double v_len_sqr;
	double v_len;

	v_len_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
	v_len = sqrt(v_len_sqr);
	return (v_scale(v, 1 / v_len));
}

t_coords v_scale (t_coords v, double scale) 
{
	return ((t_coords){scale * v.x, scale * v.y, scale * v.z});
}

double		v_dot(t_coords v, t_coords u)
{
	return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
}

t_coords vector_operations(t_coords v, t_coords u, t_oper mode) 
{
	if (mode == ADD)
		return ((t_coords){(v.x + u.x), (v.y + u.y), (v.z + u.z)});
	else if (mode == SUB)
		return ((t_coords){(v.x - u.x), (v.y - u.y), (v.z - u.z)});
	else if (mode == CROSS)
		return ((t_coords){(v.y * u.z) - (v.z * u.y),
						(v.z * u.x) - (v.x * u.z),
						(v.x * u.y) - (v.y * u.x)});
}