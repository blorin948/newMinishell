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
	int ex;
	struct s_export *export;
} t_env;

typedef struct s_norm_fucker
{
	int guillemets;
	int guillemetd;
	char *line2;
	char tmp[2];
	int i;
}	t_norm_fucker;

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
int g_ret;
int create_fd(t_cmd *cmd, t_env *env);
void add_id(t_env *env);
void check_in_out(t_cmd *cmd, t_env *env);
void parse_hook_split(t_cmd *cmd);
int check_hook(char *str);
int check_in_fd(t_cmd *cmd);
char *split_line(char *str);
char *get_name(char *str, char c);
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
int remove_pipe_virgul(t_cmd *cmd);
char *parse_dollars(t_cmd *cmd, t_env *env);
void parse_all(t_env *env);
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
void free_all(t_env *env);
void split_words(char *line, t_env *env);
int pass_hook(char *str, int i);
char *replace_dollars(char *new);
char **create_tab_redir(t_cmd *cmd, int len, char redir);
int count_len2(char *line, int i);
void count_len(t_cmd *cmd, int i);
int split_rest(t_cmd *cmd);
int exit_cmd(t_env *env);
t_cmd *create_cmd(t_env *env);

#endif