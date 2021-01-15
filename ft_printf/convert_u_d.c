/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 19:55:49 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:24:55 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		*parse_unsigned(int *c, char *s, int par, int *k)
{
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'u')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		convert_type_unsigned(char *s, va_list argue, int par)
{
	unsigned long	n;
	int				i;
	int				k[3];
	int				c;
	int				z;

	z = 0;
	assign_tab(k);
	c = 0;
	i = 0;
	parse_unsigned(&c, s, par, k);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned long);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		i = ft_unsigned_len(n);
	z = add_space_before(s, i, k, par);
	z = z + add_precision(i, k[1]);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		ft_putnbr_unsigned(n, &z);
	z = z + add_space_after(s, i, k, par);
	return (z);
}

int		*parse_int(int *c, char *s, int par, int *k)
{
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'd' && s[par] != 'i')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		convert_type_int2(long n, int c)
{
	int z;

	z = 0;
	if (n < 0)
		n = n * -1;
	ft_putnbr(n, &z);
	c = c + z;
	return (c);
}

int		convert_type_int(char *s, va_list argue, int par)
{
	long	n;
	int		i;
	int		k[3];
	int		c;
	int		z;

	assign_tab(k);
	c = 0;
	i = 0;
	parse_int(&c, s, par, k);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, int);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		i = ft_intlen(n);
	if (n < 0)
		k[2] = 1;
	z = add_space_before(s, i, k, par);
	z = z + add_precision_int(i, k[1]);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		z = convert_type_int2(n, z);
	z = z + add_space_after(s, i, k, par);
	return (z);
}
