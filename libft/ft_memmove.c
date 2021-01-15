/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:28:25 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:21:39 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;

	d = (unsigned char*)dest;
	s = (unsigned char*)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (s < d)
		while (++i <= n)
			d[n - i] = s[n - i];
	else
		while (n-- > 0)
			*d++ = *s++;
	return (dest);
}
