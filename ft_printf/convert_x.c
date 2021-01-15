/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:30:55 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:24:58 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		convert_x_m(unsigned int n, int *c, unsigned int a)
{
	int				tmp;
	char			*str;

	tmp = 0;
	str = "0123456789ABCDEF";
	if (n > 0)
	{
		*c = *c + 1;
		convert_x_m(n / 16, c, a);
		tmp = n % 16;
		write(1, &str[tmp], 1);
	}
	if (a == 0)
	{
		write(1, "0", 1);
		*c = *c + 1;
	}
	return (1);
}

char	*ft_capitalize(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

int		*parse_hexa_m(int *c, char *s, int par, int *k)
{
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'X')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		convert_type_hexa_m(char *s, va_list argue, int par)
{
	unsigned int	n;
	int				i;
	int				k[3];
	int				c;

	assign_tab(k);
	i = 0;
	parse_hexa_m(&k[2], s, par, k);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (k[2] > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned int);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && k[2] > 0)) && (n == 0)))
		i = hexa_len_hexa(n);
	c = add_space_before(s, i, k, par);
	c = c + add_precision(i, k[1]);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && k[2] > 0)) && (n == 0)))
		convert_x_m(n, &c, n);
	c = c + add_space_after(s, i, k, par);
	k[2] = 0;
	return (c);
}
