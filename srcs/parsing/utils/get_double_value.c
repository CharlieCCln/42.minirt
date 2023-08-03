/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_double_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:42:30 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 16:44:19 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_double_format(char *content)
{
	int	i;

	i = 0;
	if (content[i] == '-')
		i++;
	if (content[i] < '0' || content[i] > '9')
		return (1);
	if (content[i] == '0' && content[i + 1] && content[i + 1] != '.')
		return (1);
	while (content[i] && content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i] && (content[i] != '.' || !content[i + 1]))
		return (1);
	if (content[i])
		i++;
	while (content[i] && content[i] >= '0' && content[i] <= '9')
		i++;
	if (content[i])
		return (1);
	return (0);
}

static int	minirt_atod(double *value, char *content)
{
	int		i;
	double	overflow;

	i = 0;
	if (content[i] == '-')
		i++;
	while (content[i] && content[i] != '.')
	{
		overflow = *value;
		*value = *value * 10 + (content[i] - 48);
		if ((int)(*value / 10) != overflow)
			return (1);
		i++;
	}
	return (0);
}

int	get_double_value(double *value, char *content)
{
	int		i;
	int		pos;
	double	before;
	double	after;

	if (check_double_format(content))
		return (1);
	i = 0;
	pos = 1;
	before = 0;
	after = 0;
	if (content[0] == '-')
		pos = -1;
	if (minirt_atod(&before, content))
		return (1);
	while (content[i] && content[i] != '.')
		i++;
	if (content[i] && minirt_atod(&after, &content[i + 1]))
		return (1);
	*value = pos * (before + (after / pow(10, (ft_strlen(content) - i - 1))));
	return (0);
}
