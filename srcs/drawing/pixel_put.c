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

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int	*dst;

	if (x >= 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		dst = (int *)mlx->addr;
		dst[y * WIDTH + x] = color;
	}
}
