/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:46 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 18:03:53 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// void	parse_line_content(t_data *data, char *line)
// {
// 	char	**split;

// 	split = ft_split(line, ' ');
// 	if (!split)
// 		return (print_error("ft_split fail"), terminate(data));
// }

// void	parse_elements(t_data *data, char *filename)
// {
// 	char	*line;

// 	data->fd = open_infile(data, filename);
// 	while (42)
// 	{
// 		line = gnl_safe(data, data->fd);
// 		if (!line)
// 			break ;
// 		parse_line_content(data, line);
// 		free(line);
// 	}
// 	gnl_safe(data, -1);
// 	close(data->fd);
// }

void	check_forbidden_element(t_data *data, char *filename)
{
	char	*line;
	char	**spt;

	data->fd = open_infile(data, filename);
	while (42)
	{
		line = gnl_safe(data, data->fd);
		if (!line)
			break ;
		spt = ft_split(remove_endl(line), ' ');
		free(line);
		if (!spt)
			return (print_error("ft_split fail"), terminate(data));
		if (spt[0] && ft_strcmp(spt[0], "A") && ft_strcmp(spt[0], "C") && \
			ft_strcmp(spt[0], "L") && ft_strcmp(spt[0], "sp") && \
				ft_strcmp(spt[0], "pl") && ft_strcmp(spt[0], "cy") && \
					ft_strcmp(spt[0], "\n"))
			return (gnl_safe(data, -1), ft_freeall(spt), \
				print_error("Unknown element type"), terminate(data));
		ft_freeall(spt);
	}
	gnl_safe(data, -1);
	close(data->fd);
}

void	parsing_hub(t_data *data, char *filename)
{
	check_forbidden_element(data, filename);
	check_unique_element(data, filename, "A");
	check_unique_element(data, filename, "C");
	check_unique_element(data, filename, "L");
	parse_filename(data, filename);
	//parse_elements(data, filename);
}
