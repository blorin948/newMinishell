/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:28:20 by blorin            #+#    #+#             */
/*   Updated: 2021/01/10 14:37:43 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_redir(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->out_len != 0)
	{
		cmd->redi_out = create_tab_redir(cmd, cmd->out_len, '>');
		cmd->out = 3;
	}
	if (cmd->in_len != 0)
	{
		cmd->redi_in = create_tab_redir(cmd, cmd->in_len, '<');
		cmd->in = 3;
	}
}

void	parse_hook_split(t_cmd *cmd)
{
	int i;

	i = 0;
	count_len(cmd, i);
	copy_redir(cmd);
	split_rest(cmd);
}

void	add_id(t_env *env)
{
	int		i;
	t_cmd	*cmd;

	cmd = env->cmd;
	i = 0;
	while (cmd)
	{
		cmd->id = i;
		i++;
		cmd = cmd->next;
	}
	env->nbr = i - 1;
}

void	check_in_out(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*name;

	i = 0;
	if (cmd->id == 0 && cmd->id != env->nbr)
		cmd->out = 2;
	if (cmd->id != 0 && cmd->id != env->nbr)
	{
		cmd->out = 2;
		cmd->in = 2;
	}
	if (cmd->id != 0 && cmd->id == env->nbr)
		cmd->in = 2;
	if (cmd->out_len > 0)
	{
		while (cmd->redi_out[i])
		{
			name = get_name(cmd->redi_out[i], '>');
			if (ft_strlen(name) == 0)
				env->ex++;
			free(name);
			i++;
		}
	}
}
