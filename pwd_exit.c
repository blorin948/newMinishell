/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:32:05 by blorin            #+#    #+#             */
/*   Updated: 2021/01/15 15:21:54 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(void)
{
	char str[PATH_MAX];

	g_ret = 0;
	getcwd(str, PATH_MAX);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

void	free_export2(t_env *env)
{
	t_export *tmp;

	while (env->export)
	{
		tmp = env->export;
		env->export = env->export->next;
		free(tmp->str);
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	env->export = NULL;
}

void	free_envir2(t_env *env)
{
	t_envir *tmp;

	while (env->envir)
	{
		tmp = env->envir;
		env->envir = env->envir->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
	env->envir = NULL;
}

int		exit_cmd(t_env *env)
{
	free_export2(env);
	free_envir2(env);
	while (1)
	{
		
	}
	exit(0);
}
