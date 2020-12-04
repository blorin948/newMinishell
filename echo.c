#include "minishell.h"

int echo_cmd(t_cmd *cmd)
{
	int i = 1;
	while (cmd->split[i])
		ft_putstr(cmd->split[i++]);
	write(1, "\n", 1);
	exit(0);
}