/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:46:49 by blorin            #+#    #+#             */
/*   Updated: 2021/01/15 17:04:40 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**replace2(char **tab)
{
	int a;
	int i;

	i = 0;
	a = 0;
	while (tab[a])
	{
		while (tab[a][i])
		{
			if (tab[a][i] == '\e')
				tab[a][i] = '\'';
			if (tab[a][i] == '\b')
				tab[a][i] = '"';
			i++;
		}
		a++;
		i = 0;
	}
	return (tab);
}

void	replace(t_cmd *cmd)
{
	int i;
	int a;

	a = 0;
	i = 0;
	cmd->split = replace2(cmd->split);
	if (cmd->out_len > 0)
		cmd->redi_out = replace2(cmd->redi_out);
	if (cmd->in_len > 0)
		cmd->redi_in = replace2(cmd->redi_in);
}

void	parse_all(t_env *env)
{
	t_cmd	*cmd;
	char	*tmp;

	cmd = env->cmd;
	add_id(env);
	while (cmd)
	{
		env->i = 0;
		remove_pipe_virgul(cmd);
		tmp = cmd->line;
		cmd->line = parse_dollars(cmd, env, env->i);
		free(tmp);
		parse_hook_split(cmd);
		replace(cmd);
		check_in_out(cmd, env);
		create_fd(cmd, env);
		if ((env->i = 0) && check_in_fd(cmd) == 1)
			env->ex++;
		while (cmd->split[env->i])
		{
			cmd->split[env->i] = reverse_slash(cmd->split[env->i], env);
			env->i++;
		}
		cmd = cmd->next;
	}
}
