#include "minishell.h"

int is_char(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int is_valid(char *str)
{
	int i = 0;
	if (str[i] == '=')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
/*
char *fill_export(char *str1, char *str2)
{
	char *new;
	if (!(new = malloc(sizeof(char) * ft_strlen(str2) + 14)))
		return (NULL);
	int i = 0;
	while (str1[i])
	{
		new[i] = str1[i];
		i++;
	}
	int a = 0;
	int e = 0;
	while (str2[a])
	{
		new[i] = str2[a];
		if (str2[a] == '=' && e == 0)
		{
			i++;
			new[i] = '"';
			e++;
		}
		i++;
		a++;
	}
	new[i] = '"';
	i++;
	new[i] = '\0';
	return (new);
}
/*
char **create_export(char **tab)
{
	char **newtab;
	int i  =0;
	int a = 0;
	while (tab[i])
		i++;
	if (!(newtab = malloc(sizeof(char *) * i + 1)))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		newtab[i] = fill_export("declare -x ", tab[i]);
		i++;
	}
	newtab[i] = 0;
	return (newtab);
}*/

char **add_line(char *str, char **tab)
{
	int i = 0;
	while (tab[i])
		i++;
	char **newtab;
	if (!(newtab = malloc(sizeof(char *) * i + 2)))
		return (NULL);
	i = 0;
	int a = 0;
	while (tab[a])
	{
		if (!(newtab[a] = malloc(sizeof(char) * ft_strlen(tab[a]) + 1)))
			return (NULL);
		while (tab[a][i])
		{
			newtab[a][i] = tab[a][i];
			i++;
		}
		newtab[a][i] = '\0';
		a++;
		i = 0;
	}
	newtab[a] = ft_strdup(str);
	a++;
	newtab[a] = 0;
	return (newtab);
}

int is_already(t_export *export, char *str)
{
	int i = 0;
	while (export)
	{
		if (ft_strcmp(export->str, str) == 0)
			return (1);
		export = export->next;
	}
	return (0);
}

int export_cmd(t_cmd *cmd, t_env *env)
{
	int i = 1;
	t_export *export = env->export;
	if (!(cmd->split[1]))
	{
		while (export)
		{
			ft_putstr_fd(export->str, 1);
			ft_putstr_fd("\n", 1);
			export = export->next;
		}
	}
	i = 1;
	while (cmd->split[i])
	{
		if (is_char(cmd->split[i], '=') == 0)//pas d'egale
		{
			if (is_valid(cmd->split[i]) == 0)
			{
				if (is_already(export, ft_strjoin("declare -x ", cmd->split[i])) == 0)
				{
					fill_export(create_export(env), ft_strjoin("declare -x ", cmd->split[i]));
				}
			}
			else
				printf("error with : %s\n", cmd->split[i]);
		}
		else
		{
			if (is_valid(cmd->split[i]) == 0)
			{
				if (is_already(export, ft_strjoin("declare -x ", cmd->split[i])) == 0)
				{
					fill_envir(create_envir(env), cmd->split[i]);
					fill_export(create_export(env), ft_strjoin("declare -x ", cmd->split[i]));
				}
			}
			else
				printf("error with : %s\n", cmd->split[i]);
		}
		
		i++;
	}
	i = 0;
	return (0);
}