#include "minishell.h"

void copy_redir(t_cmd *cmd)
{
	int i = 0;
	if (cmd->out_len != 0)
	{
		cmd->redi_out = create_tab_redir(cmd, cmd->out_len, '>');
		cmd->out = 3;
	}
	if (cmd->in_len != 0)
	{
		cmd->redi_in = create_tab_redir(cmd, cmd->in_len, '<');
		cmd->in = 3;
	}
}

void parse_hook_split(t_cmd *cmd)
{
	int i = 0;
	int a = 0;
	int k = 0;
	count_len(cmd, i);
	copy_redir(cmd);
	split_rest(cmd);
	i = 0;
}

int check_error_redir(char **tab)
{
	int i = 0;
	int a = 0;
	while (tab[a])
	{
		while (tab[a][i] == '>')
		{
			i++;
		}
		if (i != 1 && i != 2)
		{
			printf("error\n");
			return (0);
		}
		a++;
	}
	return (1);
}

int is_double(char *str)
{
	int i = 0;
	while (str[i] == '>')
		i++;
	if (i == 2)
		return (1);
	else 
	return (0);
	
}

char *get_name(char *str, char c)
{
	int i = 0;
	int a = 0;
	char *new;
	while (str[i] == c)
		i++;
	i++;
	if (!(new = malloc(sizeof(char) * ft_strlen(str) - i + 1)))
		return (NULL);
	while (str[i])
	{
		new[a++] = str[i++];
	}
	new[a] = '\0';
	return (new);
}

int create_fd(t_cmd *cmd)
{
	int i = 0;
	int a = 0;
	char **tab = cmd->redi_out;
	if (!(cmd->redi_out))	
		return (1);
	if (cmd->out_len < 1)
		return (0);
	cmd->out = 3;
	check_error_redir(tab);
	while (a < cmd->out_len - 1)
	{
	if (is_double(tab[a]) == 0)
		open(get_name(tab[a], '>'), O_RDWR | O_CREAT | O_TRUNC,S_IRWXU);
	else
		open(get_name(tab[a], '>'), O_RDWR | O_CREAT | O_APPEND,S_IRWXU);
	a++;		
	}
	if (is_double(tab[a]) == 0)
		cmd->fd = open(get_name(tab[a], '>'), O_RDWR | O_CREAT | O_TRUNC,S_IRWXU);
	else
		cmd->fd = open(get_name(tab[a], '>'), O_RDWR | O_CREAT | O_APPEND,S_IRWXU);
	return (1);
}

void add_id(t_env *env)
{
	int i = 1;
	t_cmd *cmd = env->cmd;
	while (cmd)
	{
		cmd->id = i;
		i++;
		cmd = cmd->next;
	}
	env->nbr = i - 1;
}

void check_in_out(t_cmd *cmd, t_env *env)
{
	int i = 0;
	if (cmd->id == 1 && cmd->id != env->nbr)
		cmd->out = 2;
	if (cmd->id != 1 && cmd->id != env->nbr)
	{
		cmd->out = 2;
		cmd->in = 2;
	}
	if (cmd->id != 1 && cmd->id == env->nbr)
		cmd->in = 2;
	if (cmd->out_len > 0)
	{
		while (cmd->redi_out[i])
		{
			if (ft_strlen(get_name(cmd->redi_out[i], '>')) == 0)
			{
				printf("error\n");
				env->ex++;
			}
			i++;
		}
	}
}

int check_in_fd(t_cmd *cmd)
{
	int i = 0;
	struct stat s;
	if (cmd->in_len < 1)
		return (0);
	while (cmd->redi_in[i])
	{
		if (stat(get_name(cmd->redi_in[i], '<'), &s) == -1)
		{
			printf("jdois encore gerer l'erreur\n");
			return (1);
		}
	i++;
	}
	i--;
	cmd->fd_in = open(get_name(cmd->redi_in[i], '<'), O_RDONLY,S_IRWXU);
	return (0);
}

void replace(t_cmd *cmd)
{
	int i = 0;
	int a = 0;
	while (cmd->split[a])
	{
		while (cmd->split[a][i])
		{
			if (cmd->split[a][i] == '\e')
				cmd->split[a][i] = '\'';
			if (cmd->split[a][i] == '\b')
				cmd->split[a][i] = '"';
			i++;
		}
		i = 0;
		a++;
	}
	i = 0;
	a = 0;
	if (cmd->in_len > 0)
	{
	while (cmd->redi_in[a])
	{
		while (cmd->redi_in[a][i])
		{
			if (cmd->redi_in[a][i] == '\e')
				cmd->redi_in[a][i] = '\'';
			if (cmd->redi_in[a][i] == '\b')
				cmd->redi_in[a][i] = '"';
			i++;
		}
		i = 0;
		a++;
	}
	}
	if (cmd->out_len > 0)
	{
	while (cmd->redi_out[a])
	{
		while (cmd->redi_out[a][i])
		{
			if (cmd->redi_out[a][i] == '\e')
				cmd->redi_out[a][i] = '\'';
			if (cmd->redi_out[a][i] == '\b')
				cmd->redi_out[a][i] = '"';
			i++;
		}
		i = 0;
		a++;
	}
	}
}

void parse_all(t_env *env)
{
	if (env->ex > 0)
		return ;
    t_cmd *cmd;
    int i = 0;
    cmd = env->cmd;
	add_id(env);
	while (cmd)
    {
		remove_pipe_virgul(cmd);
		cmd->line = parse_dollars(cmd, env);
		parse_hook_split(cmd);
		replace(cmd);
		check_in_out(cmd, env);
		create_fd(cmd);
		//while (cmd->split[i])
		//	printf("%s\n", cmd->split[i++]);
	//	while (cmd->redi_out[i])
	//		printf("%s\n", cmd->redi_out[i++]);
		check_in_fd(cmd);
		cmd = cmd->next;
		i = 0;
    }
}

char *split_line(char *str)
{
	char *new;
	static int i =0;
	int a = i;
	if (str == NULL)
		return (NULL);
	if (str[i] == '\0')
	{
		i = 0;
		return (NULL);
	}
	while (str[i] && str[i] != ';')
	{
		if (str[i] == '"')
		{
			i++;
			while (str && str[i] != '"')
				i++;
			i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] != ';' && str[i] != '"' && str[i] != '\'')
			i++;
	}
	new = ft_substr(str, a, i - a);
	if (str[i] != '\0')
		i++;
	return (new);
}

int check_hook(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				
				i++;
			}
			if (str[i] == '\0')
				return (1);
			i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0')
				return (1);
			i++;
		}
		if (str[i] != '"' && str[i] != '\'')
			i++;
	}
	return (0);
}


void display_prompt(void)
{
    ft_putstr_fd("prompteur : ", 1);
}

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		if (g_sig == 0)
			display_prompt();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		display_prompt();
	}
}

int     main(int ac, char **av, char **envir)
{
    char *line = NULL;
	char *s_line = NULL;
    t_env *env;
	int i = 0;
    if (!(env = malloc(sizeof(t_env))))
        return (0);
	env->cmd = NULL;
	env->envir = NULL;
	env->export = NULL;
	env->env_tab = envir;
	i = 0;
	g_sig = 0;
	g_ret = 0;
	create_envir_export(env, envir);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
    while (1)
    {
		env->ex = 0;
		display_prompt();
    	if (get_next_line(0, &line)== 0)
			exit(0);
		if (check_hook(line) != 0)
		{
			printf("error\n");
			line = NULL;
		}
		while ((s_line = split_line(line)) != NULL)
		{
    		split_words(s_line, env);
    		parse_all(env);
			exec(env);
			free_all(env);
		}
	}
}