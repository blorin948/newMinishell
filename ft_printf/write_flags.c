/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:14:13 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:35:17 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_space2(int *param, int preci, char *str, int i)
{
	int space;
	int c;

	c = 0;
	space = 0;
	if (param[0] > 0)
	{
		space = param[0] - preci;
		while (space-- > 0)
		{
			write(1, " ", 1);
			c++;
		}
	}
	else
	{
		space = ft_atoi1(str, i);
		space = space - preci;
		while (space-- > 0)
		{
			write(1, " ", 1);
			c++;
		}
	}
	return (c);
}

int		write_space(char *str, int len, int *param, int i)
{
	int preci;
	int c;

	preci = 0;
	c = 0;
	if (is_string(str, i) > 0)
		preci = count_precision_string(str, len, param[1], i);
	else
		preci = count_precision(str, len, param[1], i);
	if (param[2] > 0)
		preci++;
	if (param[0] < 0)
		param[0] = param[0] * -1;
	c = write_space2(param, preci, str, i);
	return (c);
}

int		add_space_after(char *str, int len, int *param, int i)
{
	int c;

	c = 0;
	while (str[i] != '%')
		i++;
	i++;
	if (str[i] == '%')
		i++;
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' &&
			str[i] != 'p' && str[i] != 'd' && str[i] != 'i' && str[i] != 'u'
			&& str[i] != 'x' && str[i] != 'X' && str[i] != '%')
		i++;
	while (str[i - 1] != '%')
		i--;
	if (is_valid_after(str, i, param[0]) > 0)
		return (0);
	if (is_space_after(str, i) > 0)
	{
		c = write_space(str, len, param, i);
		return (c);
	}
	return (0);
}

int		add_negative(int *param, int len, int *c)
{
	if (param[2] > 0)
	{
		write(1, "-", 1);
		len++;
		*c = *c + 1;
	}
	return (len);
}
