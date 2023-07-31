/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_unique_element.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:07:38 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 17:59:30 by ccrottie         ###   ########.fr       */
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

static void	check_count(int count, char *to_check)
{
	if (count != 1)
	{
		write(2, "Error\n", 6);
		if (to_check[0] == 'A')
			write(2, "Ambient light", 13);
		else if (to_check[0] == 'C')
			write(2, "Camera", 6);
		else if (to_check[0] == 'L')
			write(2, "Light", 5);
		if (!count)
			write(2, " is not present in the file\n", 28);
		else
			write(2, " is present more than once in the file\n", 39);
		exit(1);
	}
}

void	check_unique_element(t_data *data, char *filename, char *to_check)
{
	int		count;
	char	*line;
	char	**split;

	data->fd = open_infile(data, filename);
	count = 0;
	while (42)
	{
		line = gnl_safe(data, data->fd);
		if (!line)
			break ;
		split = ft_split(remove_endl(line), ' ');
		free(line);
		if (!split)
			return (gnl_safe(data, -1), print_error("ft_split fail"), \
				terminate(data));
		if (split[0] && !ft_strcmp(split[0], to_check))
			count++;
		ft_freeall(split);
	}
	gnl_safe(data, -1);
	close(data->fd);
	check_count(count, to_check);
}
