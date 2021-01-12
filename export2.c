/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:50:47 by blorin            #+#    #+#             */
/*   Updated: 2021/01/11 14:46:19 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_valid(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		envir_cmd2(t_cmd *cmd, t_env *env, int i)
{
	t_envir *envir;
	char	*name;

	envir = env->envir;
	if (is_char(cmd->split[i], '=') == 0)
		return (0);
	if (is_valid(cmd->split[i]) == 0)
	{
		name = find_name(cmd->split[i]);
		if (is_already_envir(envir, name) == 0)
		{
			fill_envir(create_envir(env), cmd->split[i]);
			free(name);
		}
		else
		{
			if (envir_cmd3(cmd, envir, i, name) == 0)
				return (0);
		}
	}
	else
		return (1);
	return (0);
}

int		export_cmd3(t_cmd *cmd, t_export *export, int i, char *name)
{
	char	*content;
	char	*tmp;
	int		a;

	a = 0;
	while (ft_strcmp(name, export->name) != 0)
		export = export->next;
	content = find_content(cmd->split[i]);
	if (content == NULL)
		return (0);
	tmp = export->content;
	export->content = content;
	free(tmp);
	tmp = export->str;
	export->str = fill_export2(ft_strjoin("declare -x ",
	cmd->split[i]), a);
	free(tmp);
	tmp = export->name;
	export->name = name;
	free(tmp);
	return (1);
}

int		export_cmd2(t_cmd *cmd, t_env *env, int i)
{
	t_export	*export;
	char		*name;

	export = env->export;
	if (is_valid(cmd->split[i]) == 0)
	{
		name = find_name(cmd->split[i]);
		if (is_already(export, name) == 0)
		{
			fill_export(create_export(env), cmd->split[i]);
			free(name);
		}
		else
		{
			if (export_cmd3(cmd, export, i, name) == 0)
				return (0);
		}
	}
	else
		return (1);
	return (0);
}

int		export_cmd(t_cmd *cmd, t_env *env)
{
	int			i;
	t_export	*export;
	t_envir		*envir;

	envir = env->envir;
	export = env->export;
	if (!(cmd->split[1]))
	{
		while (export)
		{
			ft_printf("%s\n", export->str);
			export = export->next;
		}
	}
	export = env->export;
	i = 1;
	while (cmd->split[i])
	{
		if (export_cmd2(cmd, env, i) == 1 && (g_ret = 1))
			ft_printf("export : %s : not a valid identifier\n", cmd->split[i]);
		envir_cmd2(cmd, env, i);
		i++;
	}
	i = 0;
	return (0);
}
