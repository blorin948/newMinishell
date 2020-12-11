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
#include <math.h>
#include <limits.h>
# define TRUE 1
#define FALSE 0


int		get_next_line(int fd, char **line);
typedef struct s_env
{
    struct s_cmd *cmd;
	struct s_envir *envir;
	int nbr;
	char **env_tab;
	struct s_export *export;
} t_env;

typedef struct s_envir
{
	struct s_envir *next;
	struct s_envir *prev;
	char *str;
	char *name;
	char *content;
}t_envir;

typedef struct s_export
{
	struct s_export *next;
	struct s_export *prev;
	char *str;
}t_export;

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


int g_sig;
int ok;
void create_envir_export(t_env *env, char **tab);
t_envir *create_envir(t_env *env);
void display_prompt(void);
void fill_export(t_export *export, char *str);
void fill_envir(t_envir *envir, char *str);
t_envir *init_envir(void);
void ft_putstr(char *str);
char	*find_path(t_env *env, char *str);
int cd_cmd(t_cmd *cmd, t_env *env);
int is_builtin(t_cmd *cmd);
int unset_cmd(t_cmd *cmd, t_env *env);
int export_cmd(t_cmd *cmd, t_env *env);
int find_builtin(t_cmd *cmd, t_env *env);
int echo_cmd(t_cmd *cmd);
int ft_strcmp(char *str1, char *str2);
int create_path(t_env *env, t_cmd *cmd);
t_export *create_export(t_env *env);
t_export *init_export(void);
t_cmd *init_cmd(void);
int exec(t_env *env);
int pwd_cmd(t_cmd *cmd);
int exit_cmd(t_cmd *cmd, t_env *env);
t_cmd *create_cmd(t_env *env);

#endif