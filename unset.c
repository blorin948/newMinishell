#include "minishell.h"

int unset2(char *env, char *var)
{
	int i = 0;
	int a = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (i != ft_strlen(var))
		return (1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		if (env[i] != var[i])
			return (1);
		i++;
	}
	return (0);
}

char **remove_env(char **tab, int tmp)
{
	char **new;
	int a = 0;
	int c = 0;
	int i = 0;
	while (tab[i])
		i++;
	if (!(new = malloc(sizeof(char *) * i)))
		return (NULL);
	i = 0;
	while (tab[a])
	{
		if (a != tmp)
		{
			if (!(new[c] = malloc(sizeof(char) * ft_strlen(tab[a]) + 1)))
				return (NULL);
			while (tab[a][i])
			{
				new[c][i] = tab[a][i];
				i++;
			}
			new[c][i] = '\0';
			c++;
			i = 0;
		}
		a++;
	}
	new[c] = 0;
	return (new);
	
	
}

int unset_cmd(t_cmd *cmd, t_env *env)
{
	int replace = 0;
	int i = 1;
	int c = 0;
	int a = 0;
	char **new = env->envir;
	char **export = env->export;
	while (cmd->split[i])
	{
		while (new[a])
		{
			if (unset2(new[a], cmd->split[i]) == 0)
			{
				env->envir = remove_env(new, a);
			}
			a++;
		}
		a = 0;
		while (export[a])
		{
			if (unset2(export[a], ft_strjoin("declare -x ", cmd->split[i])) == 0)
			{
				env->export = remove_env(export, a);
			}
			a++;
		}
		a = 0;
		i++;
	}
}