/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 15:39:07 by blorin            #+#    #+#             */
/*   Updated: 2020/12/29 16:46:31 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_split(t_cmd *cmd)
{
	int i = 0;
	char *tmp;

	while (cmd->split && cmd->split[i])
	{
		free(cmd->split[i]);
		i++;
	}
	if (cmd->split)
		free(cmd->split);
	free(cmd->line);
	i = 0;
	while (cmd->newpath && cmd->newpath[i])
	{
		free(cmd->newpath[i]);
		i++;
	}
	if (cmd->newpath)
		free(cmd->newpath);
}

void free_redir(t_cmd *cmd)
{
	int i = 0;
	char *tmp;

	while (cmd->redi_in && cmd->redi_in[i])
	{
		free(cmd->redi_in[i]);
		i++;
	}
	if (cmd->redi_in)
		free(cmd->redi_in);
	i = 0;
	while (cmd->redi_out && cmd->redi_out[i])
	{
		free(cmd->redi_out[i]);
		i++;
	}
	if (cmd->redi_out)
		free(cmd->redi_out);
}

void	free_all(t_env *env)
{
	t_cmd *tmp;

	while (env->cmd)
	{
		tmp = env->cmd;
		env->cmd = env->cmd->next;
		free_split(tmp);
		free_redir(tmp);
		free(tmp);
	}
	env->cmd = NULL;
}
