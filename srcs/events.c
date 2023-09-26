/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:28:21 by ccrottie          #+#    #+#             */
/*   Updated: 2023/09/06 12:50:31 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		terminate(data);
	return (0);
}

int	call_terminate(t_data *data)
{
	terminate(data);
	return (0);
}
