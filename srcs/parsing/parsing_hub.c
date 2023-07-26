/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:07:46 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/26 15:57:01 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	arg_check(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isascii(arg[i]))
			return (1);
		i++;
	}
	if (i < 3 || ft_strcmp(&arg[i - 3], ".rt"))
		return (1);
	return (0);
}

char	*trim_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line[i] = 0;
	return (line);
}

int	open_infile(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		perror(filename);
		exit(1);
	}
	return (fd);
}

void	check_count(int count, char *to_check)
{
	if (count != 1)
	{
		write(2, "Error\n", 7);
		write(2, to_check, 2);
		if (!count)
			write(2, " is not present in the file\n", 29);
		else
			write(2, " is present more than one time in the file\n", 44);
		exit(1);
	}
}

void	check_unique_element(char *filename, char *to_check)
{
	int		fd;
	int		count;
	char	*line;
	char	**split_line;

	fd = open_infile(filename);
	count = 0;
	while (42)
	{
		line = gnl_safe(fd);
		if (!line)
			break ;
		split_line = ft_split(trim_line(line), ' ');
		if (!split_line)
			return (print_error("ft_split fail"), \
				free(line), close(fd), exit(1));
		if (split_line[0] && !ft_strcmp(split_line[0], to_check))
			count++;
		ft_freeall(split_line);
		free(line);
	}
	get_next_line(-1);
	close(fd);
	check_count(count, to_check);
}

void	parsing_hub(t_data *data, char *filename)
{
	check_unique_element(filename, "A");
	check_unique_element(filename, "C");
	check_unique_element(filename, "L");
	(void)data;
	// parse_filename(data, filename);
	// parse_elements(data, fd);
}
