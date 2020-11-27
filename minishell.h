#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
# define TRUE 1
#define FALSE 0

int		get_next_line(int fd, char **line);
typedef struct s_env
{
    struct s_cmd *cmd;
	char **envir;

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
    int out;
	int len;
	int in_len;
	int out_len;
    int fd;
    
}t_cmd;

t_cmd *init_cmd(void);
t_cmd *create_cmd(t_env *env);

#endif