/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:57:12 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 14:30:40 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_object(t_data *data, char **content)
{
	data->obj_nbr++;
	if (!ft_strcmp(content[0], "sp"))
		return (parse_sphere(data, content));
	else if (!ft_strcmp(content[0], "pl"))
		return (parse_plane(data, content));
	else
		return (parse_cylinder(data, content));
}
