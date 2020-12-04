#include "minishell.h"

int exec(t_env *env)
{
	int i = 0;
	int fd_in = 0;;
	int pid;
	int p[2];
	t_cmd *cmd = env->cmd;
	while (cmd)
	{
		create_path(env, cmd);
		pipe(p);
		if ((pid = fork()) == -1)
        {
			return (0);
        }
		if (pid == 0)
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
			is_builtin(cmd, env);
			while (cmd->newpath[i])
				execve(cmd->newpath[i++], cmd->split, env->envir);
			printf("command not found \n");
			exit(0);
		}
		else
		{
			wait(NULL);
			//printf("test1\n");
			close(p[1]);
			fd_in = p[0];
			cmd = cmd->next;
		}
	}
}