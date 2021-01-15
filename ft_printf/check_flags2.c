/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:07:02 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:33:43 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_space(char *str, int i)
{
	int preci;

	preci = 0;
	if (is_precision(str, i) >= 0)
	{
		while ((str[i] == ' ' || str[i] == '0' ||
					str[i] == '-' || str[i] == '%'))
			i++;
	}
	else
	{
		while ((str[i] == ' ' || str[i] == '-' || str[i] == '%'))
			i++;
	}
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '.')
			preci++;
		i++;
	}
	return (0);
}

int		count_precision(char *str, int len, int param, int i)
{
	int preci;

	preci = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' &&
			str[i] != '.')
		i++;
	if (str[i] != '.')
		return (len);
	else if (param > 0)
	{
		if (param >= len)
			return (param);
		return (len);
	}
	preci = ft_atoi1(str, i);
	if (preci < len)
		return (len);
	return (preci);
}

int		is_string(char *str, int i)
{
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
		i++;
	if (str[i] == 's')
		return (1);
	return (0);
}

int		count_precision_string(char *str, int len, int param, int i)
{
	int preci;

	preci = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' &&
			str[i] != '.')
		i++;
	if (str[i] != '.')
		return (len);
	else if (param > 0)
	{
		if (param >= len)
			return (len);
		return (param);
	}
	preci = ft_atoi1(str, i);
	if (preci < len)
		return (preci);
	return (len);
}
