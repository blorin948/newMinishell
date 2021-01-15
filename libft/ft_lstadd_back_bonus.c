/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:56:01 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:20:52 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *a;

	a = ft_lstlast(*alst);
	if (a)
	{
		a->next = new;
		new->next = NULL;
	}
	else
	{
		*alst = new;
		(*alst)->next = NULL;
	}
}
