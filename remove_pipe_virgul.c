/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_pipe_virgul.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:23:16 by blorin            #+#    #+#             */
/*   Updated: 2020/12/29 15:20:07 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_pipe3(int out, char *str, int len, int in)
{
	char	*new;
	int		i;
	int		a;

	a = 0;
	i = 0;
	if (in != 2 && out == 2)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		while (str[a + 1] != '\0')
			new[i++] = str[a++];
		new[i] = '\0';
		return (new);
	}
	else
	{
		if (!(new = malloc(sizeof(char) * len - 2)))
			return (NULL);
		a = 1;
		while (str[a + 1] != '\0')
			new[i++] = str[a++];
		new[i] = '\0';
		return (new);
	}
}

char	*remove_pipe2(char *line, int in, int out, int len)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (in == 2 && out != 2)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		a = 1;
		while (line[a])
			new[i++] = line[a++];
		new[i] = '\0';
	}
	else if (in != 2 && out == 2)
		new = remove_pipe3(out, line, len, in);
	else if (in == 2 && out == 2)
		new = remove_pipe3(out, line, len, in);
	else
		return (line);
	free(line);
	return (new);
}

char	*remove_virgul3(char *str, int in, int out, int len)
{
	int		i;
	int		a;
	char	*new;

	i = 0;
	a = 0;
	if (in == 1 && out == 0)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		while (str[a + 1] != '\0')
			new[i++] = str[a++];
		new[i] = '\0';
		return (new);
	}
	else
	{
		if (!(new = malloc(sizeof(char) * len - 2)))
			return (NULL);
		a = 1;
		while (str[a + 1] != '\0')
			new[i++] = str[a++];
		new[i] = '\0';
		return (new);
	}
}

char	*remove_virgul2(char *line, int in, int out, int len)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (in == 1 && out == 0)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		a = 1;
		while (line[a])
			new[i++] = line[a++];
		new[i] = '\0';
	}
	else if (in == 1 && out == 0)
		new = remove_virgul3(line, in, out, len);
	else if (in == 1 && out == 1)
		new = remove_virgul3(line, in, out, len);
	else
		return (line);
	free(line);
	return (new);
}

int		remove_pipe_virgul(t_cmd *cmd)
{
	int i;
	int before;
	int after;

	i = 0;
	after = 0;
	before = 0;
	if (cmd->line[0] == '|')
		cmd->in = 2;
	if (cmd->line[ft_strlen(cmd->line) - 1] == '|')
		cmd->out = 2;
	cmd->line = remove_pipe2(cmd->line, cmd->in, cmd->out,
	ft_strlen(cmd->line));
	if (cmd->line[0] == ';')
		before = 1;
	if (cmd->line[ft_strlen(cmd->line) - 1] == ';')
		after = 1;
	cmd->line = remove_virgul2(cmd->line, before, after, ft_strlen(cmd->line));
	return (1);
}
