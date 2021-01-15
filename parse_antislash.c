/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_antiSlash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:09:59 by blorin            #+#    #+#             */
/*   Updated: 2021/01/15 17:06:35 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		countslash(char *line)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\\')
		{
			i = i + 2;
			a++;
		}
		if (line[i] != '\'')
			i++;
	}
	return (a);
}

void	fill_slash(char *str, char *line)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '\\')
		{
			str[a++] = line[i + 1];
			i = i + 2;
		}
		if (line[i] != '\'')
			i++;
	}
	str[a] = '\0';
}

void	replace_slash(char *new, char *line)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			new[a++] = line[i++];
			while (line[i] && line[i] != '\'')
				new[a++] = line[i++];
		}
		if (line[i] == '\\')
		{
			i = i + 2;
			new[a++] = '\r';
		}
		if (line[i] != '\'')
			new[a++] = line[i++];
	}
	new[a] = '\0';
}

char	*reverse_slash(char *line, t_env *env)
{
	static int	a = 0;
	int			i;

	i = 0;
	if (!env->slash)
		return (line);
	while (line[i])
	{
		if (line[i] == '\r')
			line[i] = env->slash[a++];
		i++;
	}
	if (env->slash[a] == '\0')
	{
		a = 0;
		free(env->slash);
		env->slash = NULL;
	}
	return (line);
}

char	*parse_antislash(char *line, t_env *env)
{
	int		i;
	int		a;
	char	*str;
	char	*newline;

	a = countslash(line);
	i = 0;
	if (!(str = malloc(sizeof(char) * a + 1)))
		return (NULL);
	fill_slash(str, line);
	if (!(newline = malloc(sizeof(char) * ft_strlen(line) - a + 1)))
		return (NULL);
	replace_slash(newline, line);
	free(line);
	env->slash = str;
	return (newline);
}
