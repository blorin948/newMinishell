#include "minishell.h"

char	*find_home(t_env *env)
{
	int i = 0;
	int a = 0;
	t_envir *envir = env->envir;
	while (envir)
	{
		if (ft_strcmp(envir->name, "HOME") == 0)
			return (envir->content);
		envir = envir->next;
	}
	return (NULL);
}

int echo_cmd(t_cmd *cmd)
{
	int i = 1;
	if (ft_strcmp(cmd->split[1], "-n") == 0)
		i = 2;
	while (cmd->split[i])
	{
		ft_putstr(cmd->split[i++]);
		if (cmd->split[i])
		ft_putstr(" ");
	}
	if (ft_strcmp(cmd->split[1], "-n") == 0)
		return (1);
	write(1, "\n", 1);
	return (0);
}

int cd_cmd(t_cmd *cmd, t_env *env)
{
	int i = 0;
	while (cmd->split[i])
		i++;
	if (i == 1)
	{
		if (chdir(find_home(env)) != 0)
		{
			ft_putstr("home missing\n");
		}
	}
	if (i > 2)
	{
		ft_putstr("to much arguments\n");
	}
	if (i == 2)
	{
		if (chdir(cmd->split[1]) != 0)
		{
			printf("%s : No such file or directory\n", cmd->split[1]);
		}
	}
	return (0);
}