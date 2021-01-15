/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_pourcent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:29:26 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:34:46 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_space_pourcent(char *str, int i, int *param)
{
	int preci;

	preci = 0;
	if (param[0] < 0)
		return (0);
	while ((str[i] == ' ' || str[i] == '-' || str[i] == '%'))
		i++;
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	return (0);
}

int		is_zero_pourcent(char *str, int i)
{
	int a;

	a = i;
	while (str[a] == '0' && str[i] != '\0' && str[i] != '.')
	{
		if (str[i] == '%')
			return (1);
		i++;
	}
	return (0);
}

int		write_space_pourcent(char *str, int i, int *param)
{
	int space;
	int c;

	c = 0;
	space = 0;
	if (param[0] < 0)
		param[0] = param[0] * -1;
	if (param[0] > 0)
	{
		while (param[0]-- > 1)
		{
			write(1, " ", 1);
			c++;
		}
	}
	else
	{
		space = ft_atoi1(str, i) - 1;
		while (space-- > 0)
		{
			write(1, " ", 1);
			c++;
		}
	}
	return (c);
}

int		write_zero_pourcent(char *str, int i, int *param)
{
	int zero;
	int c;

	c = 0;
	zero = 0;
	if (param[0] > 0)
	{
		zero = param[0];
		while (zero-- > 1)
		{
			write(1, "0", 1);
			c++;
		}
	}
	else
	{
		zero = ft_atoi1(str, i);
		while (zero-- > 1)
		{
			write(1, "0", 1);
			c++;
		}
	}
	return (c);
}

int		add_space_before_pourcent(char *str, int i, int *param)
{
	int c;

	c = 0;
	if (str[i] == '%')
		return (0);
	while (str[i] != '%')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i - 1] != '%')
		i--;
	if (is_space_pourcent(str, i, param) > 0)
	{
		c = write_space_pourcent(str, i, param);
		return (c);
	}
	if (is_zero_pourcent(str, i) > 0)
	{
		c = write_zero_pourcent(str, i, param);
		return (c);
	}
	return (c);
}
