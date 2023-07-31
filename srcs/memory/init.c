/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:39:32 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 17:07:21 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bzero_everything(t_data *data)
{
	ft_bzero(&data->mlx, sizeof(t_mlx));
	ft_bzero(&data->ambient.color, sizeof(t_color));
	ft_bzero(&data->ambient, sizeof(t_ambient));
	ft_bzero(&data->cam.coords, sizeof(t_coords));
	ft_bzero(&data->cam.vector, sizeof(t_coords));
	ft_bzero(&data->cam, sizeof(t_cam));
	ft_bzero(&data->light.coords, sizeof(t_coords));
	ft_bzero(&data->light, sizeof(t_light));
	data->objects = NULL;
	data->fd = 0;
}
