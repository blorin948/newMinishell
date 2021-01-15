/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 19:14:52 by blorin            #+#    #+#             */
/*   Updated: 2021/01/15 17:04:18 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *cmd, int i, t_env *env)
{
	char	*var;
	int		a;
	int		tmp;
	char	*var2;

	a = 0;
	tmp = i;
	while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || cmd[i] == '_'))
		i++;
	if (!(var = malloc(sizeof(char) * (i - tmp + 1))))
		return (NULL);
	i = tmp;
	while (cmd[i] && (ft_isalpha(cmd[i]) == 1 || cmd[i] == '_'))
		var[a++] = cmd[i++];
	var[a] = '\0';
	var2 = comp_var(var, env);
	free(var);
	return (var2);
}

char	*parse_dollars3(char *tmp, char *tmp_free, char *new)
{
	tmp[0] = '$';
	tmp[1] = '\0';
	tmp_free = new;
	new = ft_strjoin(new, tmp);
	free(tmp_free);
	return (new);
}

char	*parse_dollars2(char *str, int *i, char *new, t_env *env)
{
	char tmp[2];
	char *tmp_free;
	char *tmp2;

	tmp_free = NULL;
	tmp2 = NULL;
	tmp[1] = '\0';
	if (str[*i] == '?' && (tmp_free = new))
	{
		tmp2 = ft_itoa(g_ret);
		new = ft_strjoin(new, tmp2);
		*i = *i + 1;
	}
	else if ((ft_isalpha(str[*i]) == 1) && (tmp_free = new))
	{
		tmp2 = get_var(str, *i, env);
		new = ft_strjoin(new, tmp2);
		while (ft_isalpha(str[*i]) == 1)
			*i = *i + 1;
	}
	else if (ft_isdigit(str[*i]) == 1)
		*i = *i + 1;
	else if (str[*i] != '\'' && str[*i] != '"')
		return (parse_dollars3(tmp, tmp_free, new));
	return (free_tmp(tmp2, tmp_free, new));
}

int		get_crochet(t_cmd *cmd, int cro, int i)
{
	if (cmd->line[i] == '\'')
	{
		if (cro == 0)
			cro = 1;
		else if (cro == 1)
			cro = 0;
	}
	return (cro);
}

char	*parse_dollars(t_cmd *cmd, t_env *env, int i)
{
	char	*new;
	int		cro;
	char	tmp[2];
	char	*tmp_free;

	cro = 0;
	tmp[1] = '\0';
	new = ft_strdup("");
	while (cmd->line[i])
	{
		cro = get_crochet(cmd, cro, i);
		if (cmd->line[i] == '$' && cro == 0 && (i = i + 1))
			new = parse_dollars2(cmd->line, &i, new, env);
		tmp[0] = cmd->line[i];
		if (cmd->line[i] != '\0' && (cmd->line[i] != '$' || cro == 1))
		{
			tmp_free = new;
			new = ft_strjoin(new, tmp);
			if (new)
				free(tmp_free);
		}
		if (cmd->line[i] != '\0' && (cmd->line[i] != '$' || cro == 1))
			i++;
	}
	return (new);
}
