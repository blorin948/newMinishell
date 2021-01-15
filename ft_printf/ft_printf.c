/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:15:09 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:25:05 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_pourcent(char *s)
{
	static int	i = 0;
	int			a;

	a = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd' &&
					s[i] != 'i' && s[i] != 'u' && s[i] != 'x' &&
					s[i] != 'X' && s[i] != '%')
				i++;
			a++;
			break ;
		}
		i++;
	}
	if (a > 0)
	{
		i++;
		return (1);
	}
	i = 0;
	return (0);
}

int		convert_all(t_va_list_wrap *copy, char *s, int par, char c)
{
	int z;

	z = 0;
	if (c == 'c')
		z = convert_type_char(s, copy->arg, par);
	else if (c == 's')
		z = convert_type_string(s, copy->arg, par);
	else if (c == 'p')
		z = convert_type_adress(s, copy->arg, par);
	else if (c == 'd' || c == 'i')
		z = convert_type_int(s, copy->arg, par);
	else if (c == 'u')
		z = convert_type_unsigned(s, copy->arg, par);
	else if (c == 'x')
		z = convert_type_hexa(s, copy->arg, par);
	else if (c == 'X')
		z = convert_type_hexa_m(s, copy->arg, par);
	else if (c == '%')
		z = convert_type_pourcent(s, copy->arg, par);
	return (z);
}

int		use_argue(char *s, va_list argue)
{
	char			c;
	int				par;
	int				z;
	t_va_list_wrap	copy;
	int				write;

	z = 0;
	write = 0;
	va_copy(copy.arg, argue);
	par = 0;
	while (is_pourcent(s) > 0)
	{
		write = write_between(s, write, &z);
		par = parse_str(s);
		c = what_type(s, par);
		z = z + convert_all(&copy, s, par, c);
	}
	par = parse_str(s);
	write_between(s, write, &z);
	return (z);
}

int		ft_printf(const char *s, ...)
{
	va_list	argue;
	int		z;

	z = 0;
	va_start(argue, s);
	z = use_argue((char *)s, argue);
	va_end(argue);
	return (z);
}
