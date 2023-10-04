/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:53:39 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/03 16:34:14 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	_check_counts(t_data *data, int *counts)
{
	if (counts[0] != 1)
		print_error("There should be 1 Ambient element (A)");
	if (counts[1] != 1)
		print_error("There should be 1 Camera element (C)");
	if (counts[2] != 1)
		print_error("There should be 1 Light element (L)");
	if (counts[0] != 1 || counts[1] != 1 || counts[2] != 1)
		terminate(data);
}

static void	_check_line_content(t_data *data, char **content, int *counts)
{
	if (!*content)
		return ;
	else if (!ft_strcmp(*content, "A"))
		counts[0] += 1;
	else if (!ft_strcmp(*content, "C"))
		counts[1] += 1;
	else if (!ft_strcmp(*content, "L"))
		counts[2] += 1;
	else if (!ft_strcmp(*content, "sp") || \
		!ft_strcmp(*content, "pl") || \
			!ft_strcmp(*content, "cy"))
		counts[3] += 1;
	else
	{
		ft_freeall(content);
		gnl_safe(data, -1);
		print_error("Unknown element type");
		terminate(data);
	}
}

void	check_elements(t_data *data, char *filename)
{
	int		counts[4];
	char	*line;
	char	**content;

	ft_bzero(counts, sizeof(counts));
	data->fd = open_infile(data, filename);
	while (42)
	{
		line = gnl_safe(data, data->fd);
		if (!line)
			break ;
		replace_tabs_with_spaces(line);
		content = ft_split(remove_endl(line), ' ');
		free(line);
		if (!content)
			return (gnl_safe(data, -1), print_error("ft_split fail"), \
				terminate(data));
		_check_line_content(data, content, counts);
		ft_freeall(content);
	}
	gnl_safe(data, -1);
	close(data->fd);
	_check_counts(data, counts);
	allocate_objects(data, counts);
}
