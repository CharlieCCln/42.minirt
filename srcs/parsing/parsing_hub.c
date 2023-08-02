/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:46 by ccrottie          #+#    #+#             */
/*   Updated: 2023/08/02 18:13:25 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*remove_endl(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = 0;
	return (line);
}

int	open_infile(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		perror(filename);
		terminate(data);
	}
	return (fd);
}

int	parse_line_content(t_data *data, char **content)
{
	if (!*content)
		return (0);
	else if (!ft_strcmp(*content, "A"))
		return (parse_ambient(data, content));
/* 	else if (!ft_strcmp(*content, "C"))
		return (parse_camera(data, content));
	else if (!ft_strcmp(*content, "L"))
		return (parse_light(data, content));
	else if (!ft_strcmp(*content, "sp") || \
		!ft_strcmp(*content, "pl") || \
			!ft_strcmp(*content, "cy"))
		return (parse_object(data, content)); */
	return (0);
}

void	parse_elements(t_data *data, char *filename)
{
	char	*line;
	char	**content;

	data->fd = open_infile(data, filename);
	while (42)
	{
		line = gnl_safe(data, data->fd);
		if (!line)
			break ;
		content = ft_split(remove_endl(line), ' ');
		free(line);
		if (!content || parse_line_content(data, content))
		{
			if (!content)
				print_error("ft_split fail");
			else
				ft_freeall(content);
			gnl_safe(data, -1);
			terminate(data);
		}
		ft_freeall(content);
	}
	gnl_safe(data, -1);
	close(data->fd);
}

void	parsing_hub(t_data *data, char *filename)
{
	check_elements(data, filename);
	parse_elements(data, filename);
	parse_filename(data, filename);
}
