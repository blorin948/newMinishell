/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:43:16 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:21:24 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int					i;
	unsigned char		*str;
	const unsigned char	*s;

	i = 0;
	str = dest;
	s = src;
	while (n--)
	{
		*str = *s;
		if (*s == (unsigned char)c)
		{
			i++;
			return (dest + i);
		}
		str++;
		s++;
		i++;
	}
	return (0);
}
