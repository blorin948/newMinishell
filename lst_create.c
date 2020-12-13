/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:16:42 by blorin            #+#    #+#             */
/*   Updated: 2020/12/13 20:03:25 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*line_cpy(t_cmd *cmd, char *line, int end, int start)
{
	char	*new;
	int		i;

	i = 0;
	if (!(cmd->line = malloc(sizeof(char) * end - start + 1)))
		return (0);
	if (line[end] == '|')
	{
		while (start < end)
			cmd->line[i++] = line[start++];
	}
	else if (line[end] == ';')
	{
		while (start < end)
			cmd->line[i++] = line[start++];
	}
	else
	{
		while (start < end)
			cmd->line[i++] = line[start++];
	}
	cmd->line[i] = '\0';
	return (cmd->line);
}

void	check_token_error(t_env *env)
{
	t_cmd	*new;
	int		i;
	int		c;

	c = 0;
	i = 0;
	new = env->cmd;
	while (new)
	{
		while (new->line[i])
		{
			if ((ft_isalnum(new->line[i]) == 1))
				c++;
			i++;
		}
		i = 0;
		if (c == 0)
		{
			env->ex++;
			if (env->ex == 1)
				ft_putstr_fd("syntax error near unexpected token `|'\n", 1);
		}
		c = 0;
		new = new->next;
	}
}

void	split_words(char *line, t_env *env)
{
	int start;
	int i;

	start = 0;
	i = 0;
	if (env->ex > 0)
		return ;
	while (line[i] != '\0')
	{
		i = pass_hook(line, i);
		if (line[i] == '|')
		{
			line_cpy(create_cmd(env), line, i, start);
			start = i;
		}
		if (line[i] != '\'' && line[i] != '"')
			i++;
	}
	line_cpy(create_cmd(env), line, i, start);
	check_token_error(env);
}
