/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:54:59 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:24:38 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	convert_hexa_p(unsigned long i)
{
	char c;

	if (i == 10)
		c = 97;
	if (i == 11)
		c = 98;
	if (i == 12)
		c = 99;
	if (i == 13)
		c = 100;
	if (i == 14)
		c = 101;
	if (i == 15)
		c = 102;
	if (i == 16)
		c = 103;
	if (i < 10)
		c = i + 48;
	return (c);
}

char	convert_hexa(unsigned int i)
{
	char c;

	if (i == 10)
		c = 97;
	if (i == 11)
		c = 98;
	if (i == 12)
		c = 99;
	if (i == 13)
		c = 100;
	if (i == 14)
		c = 101;
	if (i == 15)
		c = 102;
	if (i == 16)
		c = 103;
	if (i < 10)
		c = i + 48;
	return (c);
}

int		hexa_len_hexa(unsigned int n)
{
	int i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int		hexa_len(unsigned long n)
{
	int i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*ft_strrev(char *str)
{
	int		i;
	char	tmp;
	int		a;
	int		k;

	k = 0;
	a = 0;
	i = 0;
	tmp = 0;
	while (str[i])
		i++;
	i--;
	k = i;
	while (a < i)
	{
		tmp = str[a];
		str[a] = str[i];
		str[i] = tmp;
		i--;
		a++;
	}
	return (str);
}
