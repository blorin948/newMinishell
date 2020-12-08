#include "minishell.h"

int pwd_cmd(t_cmd *cmd)
{
	char str[PATH_MAX];
	getcwd(str, PATH_MAX);
	ft_putstr_fd(str, 1);
}

int exit_cmd(t_cmd *cmd, t_env *env)
{
	exit(0);
}