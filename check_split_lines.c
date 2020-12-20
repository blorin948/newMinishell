/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_split_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:34:24 by blorin            #+#    #+#             */
/*   Updated: 2020/12/20 17:26:37 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_in_fd(t_cmd *cmd)
{
	int			i;
	struct stat	s;

	i = 0;
	if (cmd->in_len < 1)
		return (0);
	while (cmd->redi_in[i])
	{
		if (stat(get_name(cmd->redi_in[i], '<'), &s) == -1)
		{
			ft_putstr_fd("no such file or directory: ", 1);
			ft_putstr_fd(get_name(cmd->redi_in[i], '<'), 1);
			ft_putstr_fd("\n", 1);
			g_ret = 1;
			return (1);
		}
		i++;
	}
	i--;
	cmd->fd_in = open(get_name(cmd->redi_in[i], '<'), O_RDONLY, S_IRWXU);
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
