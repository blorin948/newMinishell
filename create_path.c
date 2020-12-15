/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:29:29 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:44:12 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_path(t_env *env, t_cmd *cmd)
{
	int		i;
	t_envir	*envir;

	i = 0;
	envir = env->envir;
	while (envir)
	{
		if (ft_strcmp(envir->name, "PATH") == 0 && (i = 1))
			break ;
		envir = envir->next;
	}
	if (i == 0)
	{
		cmd->newpath = ft_split(cmd->split[0], '\f');
		return (0);
	}
	i = 0;
	cmd->newpath = ft_split(envir->content, ':');
	while (cmd->newpath[i])
	{
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], "/");
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], cmd->split[0]);
		i++;
	}
	return (0);
}
