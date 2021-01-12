/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:30:53 by blorin            #+#    #+#             */
/*   Updated: 2021/01/11 14:43:29 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->split[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->split[0], "export") == 0)
		return (2);
	if (ft_strcmp(cmd->split[0], "env") == 0)
		return (3);
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		return (4);
	if (ft_strcmp(cmd->split[0], "unset") == 0)
		return (5);
	if (ft_strcmp(cmd->split[0], "pwd") == 0)
		return (6);
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		return (7);
	return (0);
}

void	env_cmd(t_env *env)
{
	int		i;
	t_envir	*envir;

	g_ret = 0;
	envir = env->envir;
	i = 0;
	while (envir)
	{
		ft_putstr_fd(envir->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(envir->content, 1);
		ft_putstr_fd("\n", 1);
		envir = envir->next;
	}
}

int		find_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->split[0], "echo") == 0)
		echo_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "export") == 0)
		export_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "env") == 0)
		env_cmd(env);
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		cd_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "unset") == 0)
		unset_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "pwd") == 0)
		pwd_cmd();
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		exit_cmd(env);
	return (1);
}
