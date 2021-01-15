/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 04:07:38 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:24:35 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		convert_type_char(char *s, va_list argue, int par)
{
	char	z;
	int		i;
	int		k[3];
	int		tmp;
	int		c;

	tmp = par;
	k[0] = 0;
	k[1] = 0;
	k[2] = 0;
	i = 1;
	while (s[par] != 'c')
	{
		if (s[par] == '*')
			k[0]++;
		par++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	z = va_arg(argue, int);
	c = add_space_before(s, i, k, tmp);
	write(1, &z, 1);
	c = add_space_after(s, i, k, tmp) + c + 1;
	return (c);
}

int		add_space_before2(char *str, int i)
{
	while (str[i] != '%')
		i++;
	i++;
	if (str[i] == '%')
	{
		i++;
		return (0);
	}
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' &&
			str[i] != 'p' && str[i] != 'd' && str[i] != 'i' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != '%')
		i++;
	while (str[i - 1] != '%')
		i--;
	return (i);
}

int		add_space_before(char *str, int len, int *param, int i)
{
	int c;

	c = 0;
	i = add_space_before2(str, i);
	if (i == 0)
		return (0);
	if (is_valid_before(str, i, param[0]) > 0)
	{
		add_negative(param, len, &c);
		return (c);
	}
	if (is_space(str, i) > 0)
	{
		c = write_space(str, len, param, i);
		add_negative(param, len, &c);
		return (c);
	}
	len = add_negative(param, len, &c);
	if (is_zero(str, i) > 0)
	{
		c = c + write_zero(str, len, param, i);
		return (c);
	}
	return (c);
}

int		add_precision_int(int len, int param)
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
