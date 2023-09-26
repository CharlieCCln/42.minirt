/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/06 12:55:33 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	This function is a homemade alternative to mlx_pixel_put, that works
	directly with the image address. It casts the address onto an int array,
	and that allows us to directly give the color (also an int) to the right
	pixel using "dst[y * WIDTH + x] = color".
*/

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int	*dst;

	if (x >= 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = (int *)mlx->addr;
		dst[y * WIDTH + x] = color;
	}
}
