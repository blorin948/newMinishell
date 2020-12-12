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

void del_envir(t_env *env, char *str)
{
	t_envir *tmp = env->envir;
	t_envir *prev;

	if (ft_strcmp(tmp->name, str) == 0)
	{
		env->envir = tmp->next;
		//free(tmp->name);
		//free(tmp->content);
		//free(tmp->str);
		free(tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
		{
			prev->next = tmp->next;
			free(tmp->name);
			free(tmp->content);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void del_export(t_env *env, char *str)
{
	t_export *tmp = env->export;
	t_export *prev;

	if (ft_strcmp(tmp->str, str) == 0)
	{
		env->export = tmp->next;
		free(tmp->str);
		free(tmp);
		return ;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, str) == 0)
		{
			prev->next = tmp->next;
			free(tmp->str);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
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
		del_envir(env, cmd->split[i]);
		del_export(env, ft_strjoin("declare -x ", cmd->split[i]));
		envir = env->envir;
		export = env->export;
		i++;
	}
}