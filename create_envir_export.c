/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envir_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:34:49 by blorin            #+#    #+#             */
/*   Updated: 2021/01/10 14:12:51 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_name(char *str)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if ((!str) && ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	i--;
	if (!(new = malloc(sizeof(char) * i + 1)))
		return (NULL);
	a = i + 1;
	i = 0;
	while (i < a)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*find_content(char *str)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if ((!str) && ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	a = i;
	while (str[i])
		i++;
	if (!(new = malloc(sizeof(char) * i - a + 1)))
		return (NULL);
	i = 0;
	while (str[a])
		new[i++] = str[a++];
	new[i] = '\0';
	return (new);
}

void	fill_export(t_export *export, char *str)
{
	int i;

	i = 0;
	export->str = fill_export2(ft_strjoin("declare -x ", str), i);
	export->name = find_name(str);
	export->content = find_content(str);
}

void	fill_envir(t_envir *envir, char *str)
{
	envir->str = str;
	envir->name = find_name(str);
	envir->content = find_content(str);
}

void	create_envir_export(t_env *env, char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		fill_envir(create_envir(env), tab[i]);
		fill_export(create_export(env), tab[i]);
		i++;
	}
}
