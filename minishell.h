#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
# define TRUE 1
#define FALSE 0

int		get_next_line(int fd, char **line);
typedef struct s_env
{
    struct s_cmd *cmd;
	char **envir;
	int nbr;
} t_env;

typedef struct s_cmd
{
    struct s_cmd *next;
    struct s_cmd *prev;
    char *line;
    char **split;
    int in;
	char **redi_in;
	char **redi_out;
	char **rest;
	int *pipefd;
    int out;
	int len;
	int in_len;
	int out_len;
    int fd;
	int id;
	int fd_in;
	char **newpath;
    
}t_cmd;

void ft_putstr(char *str);
int is_builtin(t_cmd *cmd, t_env *env);
int echo_cmd(t_cmd *cmd);
int ft_strcmp(char *str1, char *str2);
int create_path(t_env *env, t_cmd *cmd);
t_cmd *init_cmd(void);
int exec(t_env *env);
t_cmd *create_cmd(t_env *env);

#endif