/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 17:08:34 by blorin            #+#    #+#             */
/*   Updated: 2020/12/14 19:07:55 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_error_redir(char **tab)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (tab[a])
	{
		while (tab[a][i] == '>')
			i++;
		if (i != 1 && i != 2)
		{
			ft_putstr_fd("parse error near '>'\n", 1);
			return (0);
		}
		a++;
	}
	return (1);
}

int		is_double(char *str)
{
	int i;

	i = 0;
	while (str[i] == '>')
		i++;
	if (i == 2)
		return (1);
	else
		return (0);
}

char	*get_name(char *str, char c)
{
	int		i;
	int		a;
	char	*new;

	i = 0;
	a = 0;
	while (str[i] == c)
		i++;
	i++;
	if (!(new = malloc(sizeof(char) * ft_strlen(str) - i + 1)))
		return (NULL);
	while (str[i])
		new[a++] = str[i++];
	new[a] = '\0';
	return (new);
}

int		create_fd2(t_cmd *cmd)
{
	int a;

	a = 0;
	while (a < cmd->out_len - 1)
	{
		if (is_double(cmd->redi_out[a]) == 0)
		{
			if ((open(get_name(cmd->redi_out[a], '>'), O_RDWR | O_CREAT | O_TRUNC,
			S_IRWXU) == -1))
				return (0);
		}
		else
			if (open(get_name(cmd->redi_out[a], '>'), O_RDWR | O_CREAT | O_APPEND,
			S_IRWXU) == -1)
				return (0);
		a++;
	}
	if (is_double(cmd->redi_out[a]) == 0)
		cmd->fd = open(get_name(cmd->redi_out[a], '>'), O_RDWR | O_CREAT |
		O_TRUNC, S_IRWXU);
	else
		cmd->fd = (open(get_name(cmd->redi_out[a], '>'), O_RDWR | O_CREAT
		| O_APPEND, S_IRWXU));
	if (cmd->fd == -1)
		return (0);
	return (1);
}

int		create_fd(t_cmd *cmd, t_env *env)
{
	int a;

	a = 0;
	if (!(cmd->redi_out))
		return (1);
	if (cmd->out_len < 1)
		return (0);
	cmd->out = 3;
	if (check_error_redir(cmd->redi_out) == 0)
	{
		env->ex = 1;
		return (0);
	}
	if (create_fd2(cmd) == 0)
	{
		ft_putstr_fd("Error with FD opening\n", 1);
		env->ex++;
	}
	return (1);
}
