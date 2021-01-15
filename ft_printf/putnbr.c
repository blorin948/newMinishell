/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:24:14 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 18:25:25 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_unsigned(unsigned int n, int *c)
{
	if (n >= 10)
	{
		ft_putnbr_unsigned(n / 10, c);
		ft_putnbr_unsigned(n % 10, c);
	}
	else
	{
		ft_putchar(n + '0');
		*c = *c + 1;
	}
}

void	ft_putnbr(long n, int *c)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
		c = c + 1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, c);
		ft_putnbr(n % 10, c);
	}
	else
	{
		*c = *c + 1;
		ft_putchar(n + '0');
	}
}
