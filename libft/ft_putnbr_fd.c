/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:23:18 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:21:53 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n > -2147483648)
	{
		if (n < 0)
		{
			ft_putchar('-', fd);
			n = n * -1;
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else
		{
			ft_putchar(n + '0', fd);
		}
	}
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
}
