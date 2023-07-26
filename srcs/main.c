/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:47:03 by ccrottie          #+#    #+#             */
/*   Updated: 2023/07/26 14:24:11 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

int	main(int argc, char **argv)
{
	t_data	data;

	bzero_everything(&data);
	if (argc != 2 || arg_check(argv[1]))
		return (print_error("Please use \"./miniRT path/to/file.rt\""), 1);
	parsing_hub(&data, argv[1]);
	return (0);
}
