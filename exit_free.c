#include "minishell.h"

void exit_free(cmd)
{
	
}

void free_all(t_env *env)
{
	t_cmd *tmp;

	while (env->cmd)
	{
		tmp = env->cmd;
		env->cmd = env->cmd->next;
		free(tmp);
	}
	env->cmd = NULL;
}
