/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:08:29 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:21:18 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new;

	if (!(new = malloc(sizeof(t_list))))
		return (0);
	if (new == NULL)
	{
		new->next = NULL;
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}
