/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:29:29 by blorin            #+#    #+#             */
/*   Updated: 2021/01/11 14:41:05 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_path2(t_cmd *cmd, int i, char *tmp)
{
	while (cmd->newpath[i])
	{
		tmp = cmd->newpath[i];
		cmd->newpath[i] = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = cmd->newpath[i];
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], cmd->split[0]);
		free(tmp);
		i++;
	}
}

int		create_path(t_env *env, t_cmd *cmd)
{
	int		i;
	t_envir	*envir;
	char	*tmp;

	tmp = NULL;
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
	create_path2(cmd, i, tmp);
	return (0);
}

char	*comp_var(char *var, t_env *env)
{
	int		i;
	int		n;
	int		a;
	char	*new;
	t_envir *envir;

	envir = env->envir;
	i = 0;
	a = 0;
	n = 0;
	while (envir && n == 0)
	{
		if (ft_strcmp(envir->name, var) == 0)
		{
			new = ft_strdup(envir->content);
			n++;
		}
		envir = envir->next;
	}
	if (n == 0)
		new = ft_strdup("");
	return (new);
}
