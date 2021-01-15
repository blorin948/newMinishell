/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftc1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 01:26:40 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:25:11 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	what_type(char *str, int i)
{
	char		c;

	if (!str)
		return (0);
	i++;
	while (str[i] != '\0')
	{
		c = str[i];
		if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
			c == 'u' || c == 'x' || c == 'X' || c == '%')
			break ;
		i++;
	}
	return (c);
}

int		ft_unsigned_len(unsigned long n)
{
	int i;

	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int		convert_x(unsigned int n, int *c, unsigned int a)
{
	int				tmp;
	char			*str;

	tmp = 0;
	str = "0123456789abcdef";
	if (n > 0)
	{
		convert_x(n / 16, c, a);
		tmp = n % 16;
		write(1, &str[tmp], 1);
		*c = *c + 1;
	}
	if (a == 0)
	{
		write(1, "0", 1);
		*c = *c + 1;
	}
	return (1);
}
