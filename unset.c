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

void del_envir(t_envir *envir, t_env *env)
{
	t_envir *tmp;

	tmp = envir->prev;
	tmp->next = envir->next;
	free(envir->name);
	free(envir->content);
	free(envir->str);
	free(envir);
}

void del_export(t_export *export, t_env *env)
{
	t_export *tmp;

	tmp = export->prev;
	tmp->next = export->next;
	free(export->str);
	free(export);
}

int unset_cmd(t_cmd *cmd, t_env *env)
{
	int replace = 0;
	int i = 1;
	int c = 0;
	int a = 0;
	t_envir *envir = env->envir;
	t_export *export = env->export;
	while (cmd->split[i])
	{
		while (envir)
		{
			if (ft_strcmp(envir->name, cmd->split[i]) == 0)
				del_envir(envir, env);
			envir = envir->next;
		}
		while (export)
		{
			if (ft_strcmp(envir->name, cmd->split[i]) == 0)
				del_export(export, env);
			export = export->next;
		}
		envir = env->envir;
		export = env->export;
		i++;
	}
}