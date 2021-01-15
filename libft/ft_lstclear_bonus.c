/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:32:34 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:21:01 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *supr;

	supr = *lst;
	while (supr)
	{
		*lst = supr;
		del((*lst)->content);
		free(*lst);
		supr = supr->next;
	}
	*lst = NULL;
}
