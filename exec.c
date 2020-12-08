#include "minishell.h"



int exec(t_env *env)
{
	int i = 0;
	int built = 0;
	int fd_in = 0;;
	int pid;
	int cpy = 0;
	int p[2];
	t_cmd *cmd = env->cmd;
	while (cmd)
	{
		create_path(env, cmd);
		pipe(p);
		built = is_builtin(cmd);
		if (built == 0)
		{
			if ((pid = fork()) == -1)
				return (0);
		}
		cpy = dup(1);
		if (pid == 0 && built == 0)
		{
			if (cmd->in == 3)
			{
				dup2(cmd->fd_in, 0);
			}
			else
				dup2(fd_in, 0);
			if (cmd->out == 3)
			{
				dup2(cmd->fd, 1);
			}
			else if (cmd->next != NULL)
			{
				dup2(p[1], 1);
			}
			close(p[0]);
			i = 0;
			while (cmd->newpath[i])
				execve(cmd->newpath[i++], cmd->split, env->envir);
			dup2(cpy, 1);
			printf("command not found : %s\n", cmd->split[0]);
			
			exit(0);
		}
		else
		{
			if (built > 0)
			{
				if (cmd->out == 3)
				{
					
					dup2(cmd->fd, 1);
				}
				else if (cmd->next != NULL)
				{
					dup2(p[1], 1);
				}
				find_builtin(cmd, env);
			}
			dup2(cpy, 1);
			close(cpy);
			wait(NULL);
			close(p[1]);
			fd_in = p[0];
			cmd = cmd->next;
			built = 0;
		}
	}
}