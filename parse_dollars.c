/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:14:52 by blorin            #+#    #+#             */
/*   Updated: 2020/12/13 19:56:14 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		comp_var2(char *str, char *var)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i != ft_strlen(var))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != var[i])
			return (0);
		i++;
	}
	return (1);
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
	return (var2);
}

char	*parse_dollars2(char *str, int *i, char *new, t_env *env)
{
	char tmp[2];

	tmp[1] = '\0';
	*i = *i + 1;
	if (str[*i] == '?')
	{
		new = ft_strjoin(new, ft_itoa(g_ret));
		*i = *i + 1;
	}
	else if ((ft_isalpha(str[*i]) == 1))
	{
		new = ft_strjoin(new, get_var(str, *i, env));
		while (ft_isalpha(str[*i]) == 1)
			*i = *i + 1;
	}
	else if (ft_isdigit(str[*i]) == 1)
		*i = *i + 1;
	else
	{
		tmp[0] = '$';
		new = ft_strjoin(new, tmp);
	}
	return (new);
}

char	*parse_dollars(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*new;
	int		cro;
	char	tmp[2];

	cro = 0;
	i = 0;
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
		new = ft_strjoin(new, tmp);
		i++;
	}
	return (new);
}
