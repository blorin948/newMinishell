/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:46:57 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:22:58 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	end_count(char const *s1, char const *set, int i, int a)
{
	int c;
	int k;

	c = 0;
	i = 0;
	a = 0;
	k = 0;
	while (s1[i] != '\0')
		i++;
	c = (i - 1);
	while (c > 0)
	{
		while (set[a] != '\0')
			if (s1[c] == set[a++])
				k++;
		a = 0;
		c--;
		if (k == 0)
			while (c > 0)
				c--;
		else
			i--;
		k = 0;
	}
	return (i - 1);
}

static int	start_count(char const *s1, char const *set, int i, int a)
{
	int c;
	int o;

	o = 0;
	a = 0;
	c = 0;
	i = 0;
	while (s1[c] != '\0')
	{
		while (set[a] != '\0')
		{
			if (s1[c] == set[a++])
				o++;
		}
		c++;
		a = 0;
		if (o == 0)
			while (s1[c] != '\0')
				c++;
		else
			i++;
		o = 0;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		a;
	int		o;
	char	*str;

	o = 0;
	a = 0;
	i = 0;
	while (s1[i] != '\0')
		i++;
	a = end_count(s1, set, i, a) - start_count(s1, set, i, a);
	a = a + 1;
	if (a <= 0)
		a = 0;
	if (!(str = malloc(sizeof(char) * a + 1)))
		return (0);
	a = start_count(s1, set, i, a);
	i = end_count(s1, set, i, a);
	while (a < (i + 1))
	{
		str[o++] = s1[a++];
	}
	str[o] = '\0';
	return (str);
}
