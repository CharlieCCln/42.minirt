/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:14:48 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 18:03:32 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_filename(t_data *data, char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	i--;
	while (i > 0 && filename[i] != '/')
		i--;
	data->mlx.win_name = ft_strdup(&filename[i + 1]);
	if (!data->mlx.win_name)
	{
		print_error("parse_filename fail");
		terminate(data);
	}
}
