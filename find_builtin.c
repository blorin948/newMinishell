#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->split[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->split[0], "export") == 0)
		return (2);
	if (ft_strcmp(cmd->split[0], "env") == 0)
		return (3);
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		return (4);
	if (ft_strcmp(cmd->split[0], "unset") == 0)
		return (5);
	if (ft_strcmp(cmd->split[0], "pwd") == 0)
		return (6);
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		return (7);
	return (0);
}

void env_cmd(t_cmd *cmd, t_env *env)
{
	int i = 0;
	while (env->envir[i])
		printf("%s\n", env->envir[i++]);
}

int find_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->split[0], "echo") == 0)
		echo_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "export") == 0)
		export_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "env") == 0)
		env_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		cd_cmd(cmd, env);
	if (ft_strcmp(cmd->split[0], "unset") == 0)
		unset_cmd(cmd, env);
	/*if (ft_strcmp(cmd->split[0], "pwd") == 0)
		pwd_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		exit_cmd(cmd);*/
}