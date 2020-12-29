/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:14:52 by blorin            #+#    #+#             */
/*   Updated: 2020/12/29 16:58:57 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_var(char *cmd, int i, t_env *env)
{
	char	*var;
	int		a;
	int		tmp;
	char	*var2;

	a = 0;
	tmp = i;
	while (cmd[i] && ft_isalpha(cmd[i]) == 1)
		i++;
	if (!(var = malloc(sizeof(char) * (i - tmp + 1))))
		return (NULL);
	i = tmp;
	while (cmd[i] && ft_isalpha(cmd[i]) == 1)
		var[a++] = cmd[i++];
	var2 = comp_var(var, env);
	free(var);
	return (var2);
}

char	*parse_dollars2(char *str, int *i, char *new, t_env *env)
{
	char tmp[2];
	char *tmp_free = NULL;
	char *tmp2 = NULL;

	tmp[1] = '\0';
	*i = *i + 1;
	if (str[*i] == '?')
	{
		tmp_free = new;
		tmp2 = ft_itoa(g_ret);
		new = ft_strjoin(new, tmp2);
		*i = *i + 1;
	}
	else if ((ft_isalpha(str[*i]) == 1))
	{
		tmp_free = new;
		tmp2 = get_var(str, *i, env);
		new = ft_strjoin(new, tmp2);
		while (ft_isalpha(str[*i]) == 1)
			*i = *i + 1;
	}
	else if (ft_isdigit(str[*i]) == 1)
		*i = *i + 1;
	else if (str[*i] != '\'' && str[*i] != '"')
	{
		tmp[0] = '$';
		tmp_free = new;
		new = ft_strjoin(new, tmp);
	}
	if (tmp_free)
		free(tmp_free);
	if (tmp2)
		free(tmp2);
	return (new);
}

char	*parse_dollars(t_cmd *cmd, t_env *env, int i)
{
	char	*new;
	int		cro;
	char	tmp[2];
	char *tmp_free;

	cro = 0;
	tmp[1] = '\0';
	new = ft_strdup("");
	while (cmd->line[i])
	{
		if (cmd->line[i] == '\'')
		{
			if (cro == 0)
				cro = 1;
			else if (cro == 1)
				cro = 0;
		}
		if (cmd->line[i] == '$' && cro == 0)
			new = parse_dollars2(cmd->line, &i, new, env);
		tmp[0] = cmd->line[i];
		if (cmd->line[i] != '$' || cro == 1)
		{
			tmp_free = new;
			new = ft_strjoin(new, tmp);
			if (new)
				free(tmp_free);
		}
		if (cmd->line[i] != '$' || cro == 1)
			i++;
	}
	return (new);
}
