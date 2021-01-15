/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftc2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 22:57:06 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:48:21 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi1(char *str, int i)
{
	int n;

	n = 0;
	while (str[i] == ' ' || str[i] == '.' ||
			str[i] == '-' || str[i] == '%' || str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n);
}

int		add_precision(int len, int param)
{
	int c;

	c = 0;
	while (len < param)
	{
		write(1, "0", 1);
		len++;
		c++;
	}
	return (c);
}

int		ft_intlen(long n)
{
	int len;

	len = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int		ft_strlen1(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (!str)
		i = 6;
	return (i);
}

int		ft_putstr1(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}
