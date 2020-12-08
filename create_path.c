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
}