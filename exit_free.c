/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:39:07 by blorin            #+#    #+#             */
/*   Updated: 2020/12/20 15:39:12 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_env *env)
{
	t_cmd *tmp;

	while (env->cmd)
	{
		tmp = env->cmd;
		env->cmd = env->cmd->next;
		free(tmp);
	}
	env->cmd = NULL;
}
