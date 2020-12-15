/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:32:05 by blorin            #+#    #+#             */
/*   Updated: 2020/12/15 17:32:23 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd_cmd(t_cmd *cmd)
{
	char str[PATH_MAX];

	getcwd(str, PATH_MAX);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

int		exit_cmd(t_env *env)
{
	exit(0);
}
