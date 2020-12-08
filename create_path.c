#include "minishell.h"

char	*find_path(t_env *env, char *str)
{
	int i = 0;
	int a = 0;
	while (env->envir[a])
	{
		while (env->envir[a][i] != '=')
			i++;
		if (ft_strncmp(env->envir[a], str, i) == 0)
			return (env->envir[a]);
		a++;
		i = 0;
	}
	return (NULL);
}

int create_path(t_env *env, t_cmd *cmd)
{
	int i = 0;
	if (cmd->split[0][0] == '/')
	{
		if (!(cmd->newpath = malloc(sizeof(char *) * 2)))
			return (0);
		cmd->newpath[0] = ft_strdup(cmd->split[0]);
		cmd->newpath[1] = 0;
		return (0);
	}
	if (find_path(env, "PATH") == NULL)
	{
		printf("rate\n");
		return (1);
	}
	cmd->newpath = ft_split(find_path(env, "PATH"), ':');
	while (cmd->newpath[i])
	{
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], "/");
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], cmd->split[0]);
		i++;
	}
	return (0);
}