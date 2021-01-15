/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:33:04 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:22:29 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen1(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		a;

	a = 0;
	i = ft_strlen1(s1) + ft_strlen1(s2);
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s1[a] != '\0')
	{
		str[i] = s1[a];
		a++;
		i++;
	}
	a = 0;
	while (s2[a] != '\0')
	{
		str[i] = s2[a];
		a++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
