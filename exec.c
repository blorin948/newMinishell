/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:44:36 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 17:30:11 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec3(t_cmd *cmd, t_exec *exec, t_env *env)
{
	if (exec->built > 0)
	{
		if (cmd->out == 3)
			dup2(cmd->fd, 1);
		else if (cmd->next != NULL)
			dup2(exec->p[1], 1);
		find_builtin(cmd, env);
	}
	dup2(exec->cpy, 1);
	close(exec->cpy);
	wait(NULL);
	close(exec->p[1]);
	exec->fd_in = exec->p[0];
	exec->built = 0;
}

int			exec2(t_cmd *cmd, t_exec *exec, t_env *env)
{
	exec->cpy = dup(1);
	exec->i = 0;
	if (cmd->in == 3)
		dup2(cmd->fd_in, 0);
	else
		dup2(exec->fd_in, 0);
	if (cmd->out == 3)
		dup2(cmd->fd, 1);
	else if (cmd->next != NULL)
		dup2(exec->p[1], 1);
	ok = 1;
	close(exec->p[0]);
	execve(cmd->split[0], cmd->split, env->env_tab);
	create_path(env, cmd);
	while (cmd->newpath[exec->i])
		execve(cmd->newpath[exec->i++], cmd->split, env->env_tab);
	dup2(exec->cpy, 1);
	ft_putstr_fd("command not found : ", 1);
	ft_putstr_fd(cmd->split[0], 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}

t_exec		*init_exec(void)
{
	t_exec *exec;

	if (!(exec = malloc(sizeof(t_exec))))
		return (NULL);
	exec->i = 0;
	exec->built = 0;
	exec->fd_in = 0;
	exec->pid = 0;
	exec->cpy = 0;
	return (exec);
}

int			exec(t_env *env)
{
	t_exec	*exec;
	t_cmd	*cmd;

	if (env->ex > 0)
		return (0);
	exec = init_exec();
	cmd = env->cmd;
	while (cmd)
	{
		pipe(exec->p);
		exec->built = is_builtin(cmd);
		if (exec->built == 0 && (g_sig = 1))
		{
			if ((exec->pid = fork()) == -1)
				return (0);
		}
		exec->cpy = dup(1);
		if (exec->pid == 0 && exec->built == 0)
			exec2(cmd, exec, env);
		else
			exec3(cmd, exec, env);
		cmd = cmd->next;
		g_sig = 0;
	}
	return (0);
}
