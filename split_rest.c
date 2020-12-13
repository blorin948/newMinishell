/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 21:03:21 by blorin            #+#    #+#             */
/*   Updated: 2020/12/13 21:55:39 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_norm_fucker	*malloc_struct(void)
{
	t_norm_fucker *s;

	if (!(s = malloc(sizeof(t_norm_fucker))))
		return (NULL);
	s->i = 0;
	s->line2 = ft_strdup("");
	s->tmp[1] = '\0';
	s->guillemets = 0;
	s->guillemetd = 0;
	return (s);
}

char			*split_rest2(char *str)
{
	t_norm_fucker *s;

	s = malloc_struct();
	while (str[s->i] && (s->tmp[0] = str[s->i]))
	{
		if (str[s->i] == '"' && s->guillemetd == 0 && s->guillemets == 0)
			s->guillemetd = 1;
		else if (str[s->i] == '"')
			s->guillemetd = 0;
		if (str[s->i] == 39 && s->guillemets == 0 && s->guillemetd == 0)
			s->guillemets = 1;
		else if (str[s->i] == 39)
			s->guillemets = 0;
		if (str[s->i] == ' ' && (s->guillemetd == 1 || s->guillemets == 1)
		&& (s->tmp[0] = '\a'))
			s->line2 = ft_strjoin(s->line2, s->tmp);
		else if (str[s->i] != '"' && str[s->i] != 39 && (s->tmp[0] = str[s->i]))
			s->line2 = ft_strjoin(s->line2, s->tmp);
		else if (str[s->i] == '"' && s->guillemets == 1 && (s->tmp[0] = '"'))
			s->line2 = ft_strjoin(s->line2, s->tmp);
		else if (str[s->i] == 39 && s->guillemetd == 1 && (s->tmp[0] = 39))
			s->line2 = ft_strjoin(s->line2, s->tmp);
		s->i++;
	}
	return (s->line2);
}

char			**remake(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (tab[i])
	{
		while (tab[i][j])
		{
			if (tab[i][j] == '\a')
				tab[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
	return (tab);
}

char			*split_rest3(char *line, char *new, int a, int i)
{
	while (line[i])
	{
		if (line[i] == '\'')
		{
			new[a++] = line[i++];
			while (line[i] && line[i] != '\'')
				new[a++] = line[i++];
			if (line[i] == '\'')
				new[a++] = line[i++];
		}
		else if (line[i] == '"')
		{
			new[a++] = line[i++];
			while (line[i] && line[i] != '"')
				new[a++] = line[i++];
			if (line[i] == '"')
				new[a++] = line[i++];
		}
		while (line[i] == '>' || line[i] == '<')
			i = i + count_len2(line, i);
		if (line[i] != '\'' && line[i] != '"')
			new[a++] = line[i++];
	}
	new[a] = '\0';
	return (new);
}

int				split_rest(t_cmd *cmd)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!(new = malloc(sizeof(char) * cmd->len)))
		return (0);
	new = split_rest3(cmd->line, new, a, i);
	new = split_rest2(new);
	cmd->line = new;
	cmd->split = NULL;
	cmd->split = ft_split(new, ' ');
	i = 0;
	cmd->split = remake(cmd->split);
	return (1);
}
