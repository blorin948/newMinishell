/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 19:04:11 by blorin            #+#    #+#             */
/*   Updated: 2020/12/20 17:33:24 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
#include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <limits.h>
# define TRUE 1
# define FALSE 0

typedef struct	s_env
{
	struct s_cmd	*cmd;
	struct s_envir	*envir;
	int				nbr;
	char			**env_tab;
	int				ex;
	int				is_fork;
	struct s_export *export;
}				t_env;

typedef struct	s_norm_fucker
{
	int				guillemets;
	int				guillemetd;
	char			*line2;
	char			tmp[2];
	int				i;
}				t_norm_fucker;

typedef struct	s_envir
{
	struct s_envir	*next;
	struct s_envir	*prev;
	char			*str;
	char			*name;
	char			*content;
}				t_envir;

typedef struct	s_export
{
	struct s_export	*next;
	struct s_export	*prev;
	char			*name;
	char			*content;
	char			*str;
}				t_export;

typedef struct	s_exec
{
	int i;
	int built;
	int fd_in;
	pid_t pid;
	int cpy;
	int p[2];
}				t_exec;

typedef struct	s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	int				nb;
	char			*line;
	char			**split;
	int				in;
	char			**redi_in;
	char			**redi_out;
	char			**rest;
	int				*pipefd;
	int				out;
	int				len;
	int				in_len;
	int				out_len;
	int				fd;
	int				id;
	int				fd_in;
	char			**newpath;
}				t_cmd;

int				g_sig;
int				g_ret;
int				get_next_line(int fd, char **line);
int				is_already(t_export *export, char *str);
int				is_already_envir(t_envir *envir, char *str);
int				create_fd(t_cmd *cmd, t_env *env);
void			add_id(t_env *env);
void			check_in_out(t_cmd *cmd, t_env *env);
void			parse_hook_split(t_cmd *cmd);
int				check_hook(char *str);
int				check_in_fd(t_cmd *cmd);
char			*find_name(char *str);
char			*find_content(char *str);
char			*fill_export2(char *str, int i);
int				is_valid(char *str);
int				is_char(char *str, char c);
char			*split_line(char *str);
char			*get_name(char *str, char c);
void			create_envir_export(t_env *env, char **tab);
t_envir			*create_envir(t_env *env);
void			display_prompt(void);
void			fill_export(t_export *export, char *str);
void			fill_envir(t_envir *envir, char *str);
t_envir			*init_envir(void);
void			ft_putstr(char *str);
char			*find_path(t_env *env, char *str);
int				cd_cmd(t_cmd *cmd, t_env *env);
int				is_builtin(t_cmd *cmd);
int				remove_pipe_virgul(t_cmd *cmd);
char			*parse_dollars(t_cmd *cmd, t_env *env, int i);
void			parse_all(t_env *env);
void			unset_cmd(t_cmd *cmd, t_env *env);
int				export_cmd(t_cmd *cmd, t_env *env);
int				find_builtin(t_cmd *cmd, t_env *env);
int				echo_cmd(t_cmd *cmd);
int				ft_strcmp(char *str1, char *str2);
int				create_path(t_env *env, t_cmd *cmd);
t_export		*create_export(t_env *env);
t_export		*init_export(void);
t_cmd			*init_cmd(void);
int				exec(t_env *env);
void			pwd_cmd(t_cmd *cmd);
void			free_all(t_env *env);
void			split_words(char *line, t_env *env);
int				pass_hook(char *str, int i);
char			*replace_dollars(char *new);
char			**create_tab_redir(t_cmd *cmd, int len, char redir);
int				count_len2(char *line, int i);
void			count_len(t_cmd *cmd, int i);
int				split_rest(t_cmd *cmd);
int				exit_cmd(t_env *env);
t_cmd			*create_cmd(t_env *env);

#endif
