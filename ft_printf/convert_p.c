/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:19:30 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:49:22 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_p(int n)
{
	char *str;

	str = convert_p(n);
	ft_putstr1(str);
	return (1);
}

void	ft_free1(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int		convert_x_p(unsigned long n, int *c, unsigned long a)
{
	int				tmp;
	char			*str;

	tmp = 0;
	str = "0123456789abcdef";
	if (n > 0)
	{
		*c = *c + 1;
		convert_x_p(n / 16, c, a);
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

char	*add_0x(char *str)
{
	int		i;
	char	*new;
	int		a;
	int		c;

	a = 0;
	i = 0;
	c = ft_strlen1(str);
	if (!(new = malloc(sizeof(char) * (c + 3))))
		return (0);
	new[i++] = '0';
	new[i++] = 'x';
	while (c > 0)
	{
		new[i] = str[a];
		i++;
		a++;
		c--;
	}
	new[i] = '\0';
	ft_free1(str);
	return (new);
}

char	*convert_p(unsigned long n)
{
	unsigned long	tmp;
	char			*str;
	int				i;
	char			c;

	tmp = 0;
	i = hexa_len(n);
	if (!(str = malloc(sizeof(char) * i)))
		return (0);
	i = 0;
	if (n == 0)
		str[i] = '0';
	while (n > 0)
	{
		tmp = n % 16;
		c = convert_hexa_p(tmp);
		str[i] = c;
		i++;
		n = n / 16;
	}
	str = ft_strrev(str);
	str = add_0x(str);
	return (str);
}
