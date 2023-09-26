/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:38:58 by ccrottie          #+#    #+#             */
/*   Updated: 2022/11/15 17:53:18 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_maketrim(char const *s1, char const *set, char *trim, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && ft_inset(set, s1[i]) != 0)
		i++;
	while (j < len)
	{
		trim[j] = s1[i];
		i++;
		j++;
	}
	trim[j] = 0;
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_inset(set, s1[i]) != 0)
		i++;
	while (s1[i] && j > 0 && ft_inset(set, s1[j - 1]) != 0)
	{
		j--;
		i++;
	}
	len = ft_strlen(s1) - i;
	trim = malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (NULL);
	return (ft_maketrim(s1, set, trim, len));
}
