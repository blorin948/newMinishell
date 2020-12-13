/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:39:27 by blorin            #+#    #+#             */
/*   Updated: 2020/12/13 21:02:10 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_len2(char *line, int i)
{
	int count;

	count = i;
	while (line[i] && line[i] == '>')
		i++;
	while (line[i] && line[i] == '<')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		i = pass_hook(line, i);
		if ((line[i] == '\0' || line[i] == ' ') && line[i]
		!= '"' && line[i] != '\'')
			return (i - count);
		if (line[i] != '\'' && line[i] != '"')
			i++;
	}
	return (i - count);
}

char	*fill_tab2(char *line, char *tab, int i, int a)
{
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'' && (i = i + 1))
		{
			while (line[i] != '\'')
				tab[a++] = line[i++];
			i++;
		}
		else if (line[i] == '"' && (i = i + 1))
		{
			while (line[i] != '"')
				tab[a++] = line[i++];
			i++;
		}
		tab[a++] = line[i++];
	}
	tab[a] = '\0';
	return (tab);
}

char	*fill_tab(char *line, int i, int len, char redir)
{
	char	*tab;
	int		a;

	a = 0;
	if (!(tab = malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (line[i] && line[i] == redir)
		tab[a++] = line[i++];
	tab[a++] = ' ';
	while (line[i] && line[i] == ' ')
		i++;
	tab = fill_tab2(line, tab, i, a);
	return (tab);
}

int		count_len_redir(char *line, int i)
{
	int count;
	int c;

	count = i;
	c = 0;
	while (line[i] && line[i] == '>')
		i++;
	while (line[i] && line[i] == '<')
		i++;
	while (line[i] && line[i] == ' ')
	{
		i++;
		c++;
	}
	while (line[i])
	{
		i = pass_hook(line, i);
		if ((line[i] == '\0' || line[i] == ' '))
			return (i - count - c);
		if (line[i] != '\'' && line[i] != '"')
			i++;
	}
	return (i - count - c);
}

char	**create_tab_redir(t_cmd *cmd, int len, char redir)
{
	char	**tab;
	int		i;
	int		a;
	int		k;

	i = 0;
	a = 0;
	k = 0;
	if (!(tab = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	while (cmd->line[i])
	{
		i = pass_hook(cmd->line, i);
		if (cmd->line[i] == redir)
		{
			k = count_len_redir(cmd->line, i);
			tab[a] = fill_tab(cmd->line, i, k, redir);
			a++;
			i = i + k - 1;
		}
		if (cmd->line[i] != '\'' && cmd->line[i] != '"')
			i++;
	}
	tab[a] = 0;
	return (tab);
}
