#include "minishell.h"

int is_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->split[0], "echo") == 0)
		echo_cmd(cmd);
	/*if (ft_strcmp(cmd->split[0], "export") == 0)
		export_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "env") == 0)
		env_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "cd") == 0)
		cd_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "unset") == 0)
		unset_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "pwd") == 0)
		pwd_cmd(cmd);
	if (ft_strcmp(cmd->split[0], "exit") == 0)
		exit_cmd(cmd);*/
}