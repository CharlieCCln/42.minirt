/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:02:21 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/21 11:03:41 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_signcheck(const char *s, int *len, va_list args)
{
	int	sec;

	if (s[0] == 'c')
		sec = ft_putchar(va_arg(args, int), len);
	else if (s[0] == 's')
		sec = ft_putstr(va_arg(args, const char *), len);
	else if (s[0] == 'p')
	{
		if (ft_putadd(len) == -1)
			return (-1);
		sec = ft_putnbr_ptr(va_arg(args, unsigned long long int), len, 0);
	}
	else if (s[0] == 'd' || s[0] == 'i')
		sec = ft_putnbr(va_arg(args, int), len, 0);
	else if (s[0] == 'u')
		sec = ft_putnbru(va_arg(args, unsigned int), len, 0);
	else if (s[0] == 'x')
		sec = ft_putnbr_hex(va_arg(args, unsigned int), len, 0, 0);
	else if (s[0] == 'X')
		sec = ft_putnbr_hex(va_arg(args, unsigned int), len, 1, 0);
	else if (s[0] == '%')
		sec = ft_putchar('%', len);
	else
		sec = -2;
	return (sec);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	int		sec;
	va_list	args;

	va_start(args, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '%')
			if (ft_putchar(s[i++], &len) == -1)
				return (va_end(args), -1);
		if (s[i] && s[i + 1])
		{
			sec = ft_signcheck(&s[i + 1], &len, args);
			if (sec == -1)
				return (va_end(args), -1);
			else if (sec != -2)
				i++;
		}
		if (s[i])
			i++;
	}
	return (va_end(args), len);
}
