/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_safe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 14:19:53 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/31 17:16:59 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*ft_strjoin_and_free(t_data *data, char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (print_error("GNL fail"), free(s1), \
			free(s2), terminate(data), NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = 0;
	return (free(s1), join);
}

static char	*trim_line(t_data *data, char *line, char *buf)
{
	int		i;
	int		len;
	char	*trim;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len])
		len++;
	trim = malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (print_error("GNL fail"), free(buf), terminate(data), NULL);
	i = 0;
	while (i < len)
	{
		trim[i] = line[i];
		i++;
	}
	trim[i] = 0;
	free(line);
	return (trim);
}

static char	*get_buf(char *line, char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i])
		i++;
	while (line[i] && j < BUFFER_SIZE)
	{
		buf[j] = line[i];
		i++;
		j++;
	}
	while (j < BUFFER_SIZE)
	{
		buf[j] = 0;
		j++;
	}
	return (buf);
}

static char	*fd_read(t_data *data, int fd, char *buf)
{
	char	*line;
	int		ret;

	ret = 1;
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (print_error("GNL fail"), free(buf), terminate(data), NULL);
	line[0] = 0;
	if (buf[0])
	{
		line = ft_strjoin_and_free(data, line, buf);
		if (!line)
			return (NULL);
	}
	while (!ft_strchr(buf, '\n') && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (!ret && !buf[0])
			return (free(line), NULL);
		buf[ret] = 0;
		line = ft_strjoin_and_free(data, line, buf);
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*gnl_safe(t_data *data, int fd)
{
	static char	*buf;
	char		*line;

	if (fd == -1 || read(fd, 0, 0) == -1)
		return (free(buf), buf = NULL, NULL);
	if (!buf)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (print_error("GNL fail"), terminate(data), NULL);
		buf[0] = 0;
	}
	line = fd_read(data, fd, buf);
	if (!line)
		return (free(buf), buf = NULL, NULL);
	buf = get_buf(line, buf);
	line = trim_line(data, line, buf);
	if (!line)
		return (free(buf), buf = NULL, NULL);
	return (line);
}
