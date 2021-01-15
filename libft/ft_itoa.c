/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:33:16 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:20:48 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*itoa2(char *str, long int n, int c)
{
	int i;
	int a;

	i = 0;
	a = 0;
	if (c > 0)
		i++;
	while (n >= 10)
	{
		a = n % 10;
		str[i] = (a + 48);
		i++;
		n = n / 10;
	}
	if (n < 10)
		str[i] = (n + 48);
	i++;
	str[i] = '\0';
	return (str);
}

static long int		positive(long int n)
{
	if (n < 0)
		n = (n * -1);
	return (n);
}

static char			*swap(char *str, int c)
{
	int i;
	int a;
	int t;

	t = 0;
	i = 0;
	a = 0;
	if (c > 0)
		a++;
	while (str[i] != '\0')
		i++;
	i--;
	while (i > a)
	{
		t = str[i];
		str[i] = str[a];
		str[a] = t;
		i--;
		a++;
	}
	return (str);
}

static int			intlen(long int n)
{
	int i;
	int a;

	a = 0;
	i = 1;
	if (n < 0)
	{
		n = (n * -1);
		a++;
	}
	while (n > 10)
	{
		n = n / 10;
		i++;
	}
	if (a > 0)
		i++;
	return (i);
}

char				*ft_itoa(int n)
{
	int			i;
	char		*str;
	int			c;
	long int	nb;

	nb = n;
	i = 0;
	c = 0;
	if (nb < 0)
		c++;
	nb = positive(nb);
	if (!(str = malloc(sizeof(char) * intlen((long int)n) + 1)))
		return (0);
	if (c == 1 && nb != 0)
	{
		str[i] = '-';
		i++;
	}
	str = itoa2(str, nb, c);
	str = swap(str, c);
	return (str);
}
/*
**int main(int ac, char **av)
**{
**	(void)ac;
**	printf("%s\n", ft_itoa(atoi(av[1])));
**}
*/
