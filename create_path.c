#include "minishell.h"


int create_path(t_env *env, t_cmd *cmd)
{
	int i = 0;
	t_envir *envir = env->envir;
	if (cmd->split[0][0] == '/')
	{
		if (!(cmd->newpath = malloc(sizeof(char *) * 2)))
			return (0);
		cmd->newpath[0] = ft_strdup(cmd->split[0]);
		cmd->newpath[1] = 0;
		return (0);
	}
	i = 0;
	while (envir)
	{
		if (ft_strcmp(envir->name, "PATH") == 0)
		{
			i = 1;
			break ;
		}
		envir = envir->next;
	}
	if (i == 0)
	{
		printf("rate\n");
		return (0);
	}
	cmd->newpath = ft_split(envir->content, ':');
	while (cmd->newpath[i])
	{
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], "/");
		cmd->newpath[i] = ft_strjoin(cmd->newpath[i], cmd->split[0]);
		i++;
	}
	return (0);
}
