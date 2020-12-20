/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:32:46 by blorin            #+#    #+#             */
/*   Updated: 2020/12/20 17:23:00 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envir(t_envir *tmp)
{
	free(tmp->name);
	free(tmp->content);
	free(tmp);
}

void	del_envir(t_env *env, char *str)
{
	t_envir *tmp;
	t_envir *prev;

	tmp = env->envir;
	if (ft_strcmp(tmp->name, str) == 0)
	{
		env->envir = tmp->next;
		free_envir(tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			prev->next = tmp->next;
			free_envir(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	free_export(t_export *tmp)
{
	free(tmp->str);
	free(tmp->name);
	free(tmp->content);
	free(tmp);
}

void	del_export(t_env *env, char *str)
{
	t_export *tmp;
	t_export *prev;

	tmp = env->export;
	if (ft_strcmp(tmp->name, str) == 0)
	{
		env->export = tmp->next;
		free_export(tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			prev->next = tmp->next;
			free_export(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset_cmd(t_cmd *cmd, t_env *env)
{
	int			i;
	t_envir		*envir;
	t_export	*export;

	i = 1;
	g_ret = 0;
	envir = env->envir;
	export = env->export;
	while (cmd->split[i])
	{
		if (is_valid(cmd->split[i]) == 1 && (g_ret = 1))
			ft_printf("export : %s : not a valid identifier\n", cmd->split[i]);
		del_envir(env, cmd->split[i]);
		del_export(env, cmd->split[i]);
		envir = env->envir;
		export = env->export;
		i++;
	}
}
