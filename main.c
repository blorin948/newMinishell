/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 19:17:36 by blorin            #+#    #+#             */
/*   Updated: 2020/12/29 16:41:33 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(void)
{
	ft_putstr_fd("prompteur : ", 1);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_ret = 130;
		ft_putstr_fd("\n", 1);
		if (g_sig == 0)
			display_prompt();
	}
	if (sig == SIGQUIT)
	{
		if (g_sig == 1)
		{
			g_ret = 131;
			ft_printf("Quit: 3\n");
		}
	}
}

int		start_loop(t_env *env, char *s_line, char *line)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		env->ex = 0;
		display_prompt();
		if (get_next_line(0, &line) == 0)
			exit(0);
		if (check_hook(line) != 0)
		{
			ft_putstr_fd("No multiline is allowed\n", 1);
			g_ret = 1;
			line = NULL;
		}
		while ((s_line = split_line(line)) != NULL)
		{
			split_words(s_line, env);
			parse_all(env);
			exec(env);
			free_all(env);
		}
		if (line)
			free(line);
	}
}

int		main(int ac, char **av, char **envir)
{
	char	*line;
	char	*s_line;
	t_env	*env;

	line = NULL;
	s_line = NULL;
	if (!(env = malloc(sizeof(t_env))))
		return (0);
	env->cmd = NULL;
	env->envir = NULL;
	env->export = NULL;
	env->env_tab = envir;
	g_sig = 0;
	g_ret = 0;
	create_envir_export(env, envir);
	start_loop(env, s_line, line);
	system("leaks checker");
}
