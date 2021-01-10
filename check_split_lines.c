/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_split_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:34:24 by blorin            #+#    #+#             */
/*   Updated: 2021/01/10 14:06:22 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_in_fd(t_cmd *cmd)
{
	int			i;
	struct stat	s;
	char		*name;

	i = 0;
	if (cmd->in_len < 1)
		return (0);
	while (cmd->redi_in[i])
	{
		name = get_name(cmd->redi_in[i], '<');
		if (stat(name, &s) == -1)
		{
			ft_printf("no such file or directory: %s\n", name);
			g_ret = 1;
			free(name);
			return (1);
		}
		free(name);
		i++;
	}
	i--;
	name = get_name(cmd->redi_in[i], '<');
	cmd->fd_in = open(name, O_RDONLY, S_IRWXU);
	free(name);
	return (0);
}

int		check_hook(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && (i += 1))
		{
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		if (str[i] == '"' && (i += 1))
		{
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		if (str[i] != '"' && str[i] != '\'')
			i++;
	}
	return (0);
}

char	*split_line(char *str)
{
	char		*new;
	static int	i = 0;
	int			a;

	a = i;
	if (str == NULL)
		return (NULL);
	if (str[i] == '\0')
	{
		i = 0;
		return (NULL);
	}
	while (str[i] && str[i] != ';')
	{
		i = pass_hook(str, i);
		if (str[i] != ';' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	new = ft_substr(str, a, i - a);
	if (str[i] != '\0')
		i++;
	return (new);
}
