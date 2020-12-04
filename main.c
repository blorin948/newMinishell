
#include "minishell.h"

void free_all(t_env *env)
{
	t_cmd *tmp;

	while (env->cmd)
	{
		tmp = env->cmd;
		env->cmd = env->cmd->next;
		free(tmp);
	}
	env->cmd = NULL;
}

void print(t_cmd *cmd)
{
    int i = 0;
char **tab;

    while (cmd)
    {
		printf("test %d = %s\n", i, cmd->line);
		if (cmd->redi_out)
		{
			tab = cmd->redi_out;
			while (tab[i])
				printf("|%s|\n", tab[i++]);
		i = 0;
		}
        cmd = cmd->next;
    }
	//printf("test %d = %s\n", i, cmd->line);
	/*if (cmd->redi_in)
	{
	char **tab = cmd->redi_in;
	while (tab[i])
		printf("|%s|\n", tab[i++]);
	}*/
	//free_all(cmd);
	//free_all(cmd);
}


void display_prompt(void)
{
    ft_putstr_fd("prompteur : ", 1);
}

char *line_cpy(t_cmd *cmd, char *line, int end, int start)
{
    char *new;
    int i = 0;
//printf("%d\n", end - start + 1);
    if (!(cmd->line = malloc(sizeof(char) * end - start + 1)))
        return (0);
	if (line[end] == '|')
	{
    	while (start < end)
    	{
        	cmd->line[i] = line[start];
        	start++;
     	   i++;
    	}
		//printf("%d  %d   %c\n", start, end, cmd->line[i]);
	}
	else if (line[end] == ';')
	{
		
		while (start < end)
    	{
        	cmd->line[i] = line[start];
        	start++;
     	   i++;
    	}
	}
	else
	{
		while (start < end)
    	{
			//printf("test 2\n");
        	cmd->line[i] = line[start];
        	start++;
     	   i++;
    	}
	}
    cmd->line[i] = '\0';
	return (cmd->line);
}

void split_words(char *line, t_env *env)
{
	t_cmd *new;
    int start = 0;
    int end = 0;
    int i = 0;
    int guill = 0;
    int cro = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '"')
        {
            if (guill == 0)
                guill = 1;
            else
                guill = 0;
        }
        if (line[i] == '\'')
        {
            if (cro == 0)
                cro = 1;
            else
                cro = 0;
        }
        if (line[i] == '|' && cro == 0 && guill == 0)
        {
            end = i;
            line_cpy(create_cmd(env), line, end, start);
            start = end;
        }
        i++;
    }
    end = i;
    line_cpy(create_cmd(env), line, end, start);
//	printf("start = %c end = %c\n", line[start], line[end - 1]);
}

char *remove_pipe2(char *line, int in, int out, int len)
{
	char *new;
	int i = 0;
	int a = 0;

	if (in == 2 && out != 2)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		a = 1;
		while (line[a])
			new[i++] = line[a++];
		new[i] = '\0';
	}
	else if (in != 2 && out == 2)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		while (line[a + 1] != '\0')
		{
			new[i] = line[a];
			i++;
			a++;
		}
		new[i] = '\0';
	}
	else if (in == 2 && out == 2)
	{
		if (!(new = malloc(sizeof(char) * len - 2)))
			return (NULL);
		a = 1;
		while (line[a + 1] != '\0')
			new[i++] = line[a++];
	}
	else
	{
		return (line);
	}
	return (new);
}

char *remove_virgul2(char *line, int in, int out, int len)
{
	char *new;
	int i = 0;
	int a = 0;

	if (in == 1 && out == 0)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		a = 1;
		while (line[a])
			new[i++] = line[a++];
		new[i] = '\0';
	}
	else if (in == 1 && out == 0)
	{
		if (!(new = malloc(sizeof(char) * len - 1)))
			return (NULL);
		while (line[a + 1] != '\0')
			new[i++] = line[a++];
		new[i] = '\0';
	}
	else if (in == 1 && out == 1)
	{
		if (!(new = malloc(sizeof(char) * len - 2)))
			return (NULL);
		a = 1;
		while (line[a + 1] != '\0')
			new[i++] = line[a++];
	}
	else
		return (line);
	return (new);
}

int remove_pipe_virgul(t_cmd *cmd)
{
    int i = 0;
	int before = 0;
	int after = 0;
    char *new;
    if (cmd->line[0] == '|')
	{
		cmd->in = 2;
	}
	if (cmd->line[ft_strlen(cmd->line) - 1] == '|')
		cmd->out = 2;
	cmd->line = remove_pipe2(cmd->line, cmd->in, cmd->out, ft_strlen(cmd->line));
	if (cmd->line[0] == ';')
		before = 1;
	if (cmd->line[ft_strlen(cmd->line) - 1] == ';')
		after = 1;
	cmd->line = remove_virgul2(cmd->line, before, after, ft_strlen(cmd->line));
	return (1);
}

char   *comp_var(char *var, t_env *env)
{
  int i = 0;
  int n = 0;
  int a = 0;
  char *new;
//    printf("%s\n", var);
  while (env->envir[a] && n == 0)
  {
      while (env->envir[a][i] && env->envir[a][i] != '=')
        i++;
       if (ft_strncmp(env->envir[a], var, i) == 0)
       {
          new = ft_strdup(env->envir[a] + (i + 1));
          n++;
             //  printf("%s\n", new);
       }
    a++;
    i = 0;
  }
//  printf("yoyo\n");
  if (n == 0)
    new = NULL;
  return (new);
}

char  *get_var(char *cmd, int i, t_env *env)
{
  char *var;
  int a = 0;
  int tmp = i;
  char *var2;
  while (cmd[i] && ft_isalnum(cmd[i]) == 1)
      i++;
  if (!(var = malloc(sizeof(char) * (i - tmp + 1))))
      return (NULL);
  i = tmp;
	while (cmd[i] && ft_isalnum(cmd[i]) == 1)
      var[a++] = cmd[i++];
  var2 = comp_var(var, env);
  return(var2);
}

char *replace_var(char *cmd, char *var, int i, t_env *env)
{
  int a = 0;
  int n  = 0;
  int tmp = i - 2;
  char *new;
   while (cmd[i] && ft_isalnum(cmd[i]) == 1)
  {
    i++;
    a++;
  }
  if (var != NULL)  
    n = ft_strlen(var);
  if (!(new = malloc(sizeof(char) * (ft_strlen(cmd) - a + n + 1))))
    return (NULL);
  i = 0;
  while (i < tmp + 1)
  {
    new[i] = cmd[i];
    i++;
  }
   int k = 0;
  a = i + a + 1;
  /*if (var == NULL)
    i = i + 2;*/
  if (var != NULL)
  {
    while (var[k]) 
      new[i++] = var[k++];
  }
    while (cmd[a])
      new[i++] = cmd[a++];
      new[i] = '\0';
      return (new);
}


char *parse_dollars(t_cmd *cmd, t_env *env)
{
	int i = 0;
  char  *var;
  int a = 0;
  char *new = cmd->line;
  int cro = 0;
  while (new[i])
  {
	if (new[i] == '\'')
	{
		if (cro == 0)
			cro = 1;
		else if (cro == 1)
			cro = 0;
	}
    if (new[i] == '$' && cro == 0)
    {
      i++;
      var = get_var(cmd->line, i, env);
      new = replace_var(cmd->line, var, i, env);
     // printf("%s\n", cmd);
      //i = 0;
    }
    i++;
  }
  return (new);	
}

int parse_hook(int i, char cmd)
{
	static int cro = 0;
	static int guill = 0;
	
	if (i == 0)
	{
		cro = 0;
		guill = 0;
	}
	if (cro == 0 && cmd == '\'')
		cro = 1;
	else if (cro == 1 && cmd == '\'')
		cro = 0;
	if (guill == 0 && cmd == '"')
		guill = 1;
	else if (guill == 1 && cmd == '"')
		guill = 0;
	if (cmd == ' ' && guill == 0 && cro == 0)
		return (1);
	if (cmd == '>' && guill == 0 && cro == 0)
		return (1);
	if (cmd == '<' && guill == 0 && cro == 0)
		return (1);
	if (cmd == '\0')
		return (2);
	return (5);
}

int count_len2(char *line, int i)
{
	int cro = 0;
	int guill = 1;
	int count = i;
	while (line[i] && line[i] == '>')
		i++;
	while (line[i] && line[i] == '<')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		while (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			i++;
		}
		while (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			i++;
		}
		if (ft_isalnum(line[i]) != 1 && line[i] != '"' && line[i] != '\'')
		{
			
			return (i - count);
		}
		i++;
	}
	//printf("i = %d count = %d  la = %d\n", i, count ,i - count);
	return (i - count);
}

void count_len(t_cmd *cmd)
{
	char *new;
	new = cmd->line;
	int i = 0;
	int cro = 0;
	int guill = 0;
	int k = 0;
	int tmp = 0;
	//cmd->len = ft_strlen(cmd->line);
	while (new[i])
	{
		if (new[i] == '\'')
		{
			if (cro == 0)
				cro = 1;
			else if (cro == 1)
				cro = 0;
		}
		if (new[i] == '"')
		{
			if (guill == 0)
				guill = 1;
			else if (guill == 1)
				guill = 0;
		}
		if (new[i] == '>' && cro == 0 && guill == 0)
		{
			cmd->out_len++;
			k = count_len2(new, i);
			tmp = tmp + k;
			i = i + k - 1;
		}
		else if (new[i] == '<' && cro == 0 && guill == 0)
		{
			cmd->in_len++;
			k = count_len2(new, i);
			tmp = tmp + k;
			i = i + k - 1;
		}
		i++;
	}
	cmd->len = i - tmp;
}

char *fill_tab(char *line, int i, int len, char redir)
{
	char *tab;
	int a = 0;
	if (!(tab = malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (line[i] && line[i] == redir)
	{
		tab[a] = line[i];
		i++;
		a++;
	}
	tab[a] = ' ';
	a++;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	while (line[i])
	{
		while (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
			{
				tab[a] = line[i];
				i++;
				a++;
			}	
		}
		while (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
			{
				tab[a] = line[i];
				i++;
				a++;
			}
			i++;
		}
		if (ft_isalnum(line[i]) != 1)
			break ;
		tab[a] = line[i];
		i++;
		a++;
	}
	tab[a] = '\0';
	return (tab);
	
}

int count_len_redir(char *line, int i)
{
	int count = i;
	int c = 0;
	while (line[i] && line[i] == '>')
		i++;
	while (line[i] && line[i] == '<')
		i++;
	while (line[i] && line[i] == ' ')
	{
		i++;
		c++;
	}
	while (line[i])
	{
		while (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			i++;
		}
		while (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			i++;
		}
		if (ft_isalnum(line[i]) != 1 && line[i] != '"' && line[i] != '\'')
		{
			
			return (i - count - c);
		}
		i++;
	}
	//printf("i = %d count = %d  la = %d\n", i, count ,i - count);
	return (i - count - c);
}

char **create_tab_redir(t_cmd *cmd, int len, char redir)
{
	char **tab;
	char *new = cmd->line;
	int i = 0;
	int a = 0;
	int k = 0;
	int cro = 0;
	int guill = 0;
	if (!(tab = malloc(sizeof(char *) * len + 1)))
		return (NULL);
	while (new[i])
	{
		if (new[i] == '\'')
		{
			if (cro == 0)
				cro = 1;
			else if (cro == 1)
				cro = 0;
		}
		if (new[i] == '"')
		{
			if (guill == 0)
				guill = 1;
			else if (guill == 1)
				guill = 0;
		}
		if (new[i] == redir && cro == 0 && guill == 0)
		{
			k = count_len_redir(new, i);
			tab[a] = fill_tab(new, i, k, redir);
			a++;
			i = i + k - 1;
		}
		i++;
	}
	tab[a] = 0;
	return (tab);
}

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

char    *split_rest2(char *str)
{
    int guillemets = 0;
    int guillemetd = 0;
    int i = 0;
    char *line2;
    char *tmp2;
    char tmp[2];
    line2 = ft_strdup("");
    tmp[1] = '\0';
    while (str[i])
    {
        tmp[0] = str[i];
        if (str[i] == '"' && guillemetd == 0 && guillemets == 0)
            guillemetd = 1;
        else if (str[i] == '"')
            guillemetd = 0;
        if (str[i] == 39 && guillemets == 0 && guillemetd == 0)
            guillemets = 1;
        else if (str[i] == 39)
            guillemets = 0;
        else if (str[i] == ' ' && (guillemetd == 1 || guillemets == 1) && (tmp[0] = '\a'))
            line2 = ft_strjoin(line2, tmp);
        else if (str[i] != '"' && str[i] != 39 && (tmp[0] = str[i]))
            line2 = ft_strjoin(line2, tmp);
        else if (str[i] == '"' && guillemets == 1 && (tmp[0] = '"'))
            line2 = ft_strjoin(line2, tmp);
        else if (str[i] == 39 && guillemetd == 1 && (tmp[0] = 39))
            line2 = ft_strjoin(line2, tmp);
        i++;
    }
    return (line2);
}

char    **remake(char **tab)
{
    int i = 0;
    int j = 0;

    while (tab[i])
    {
        while (tab[i][j])
        {
            if (tab[i][j] == '\a')
                tab[i][j] = ' ';
                j++;
        }
        j = 0;
        i++;
    }
	return (tab);
}

int split_rest(t_cmd *cmd)
{
	char *new;
	char *line = cmd->line;
	int i = 0;
	int a = 0;

	if (!(new = malloc(sizeof(char) * cmd->len)))
		return (0);
	while (line[i])
	{
		while (line[i] == '\'')
		{
			new[a++] = line[i++];
			while (line[i] && line[i] != '\'')
				new[a++] = line[i++];
		}
		while (line[i] == '"')
		{
			new[a++] = line[i++];
			while (line[i] && line[i] != '"')
				new[a++] = line[i++];
		}
		while (line[i] == '>' || line[i] == '<')
		{
			i = i + count_len2(line, i);
		}
		new[a] = line[i];
		a++;
		i++;
	}
	new[a] = '\0';
	//cmd->line = new;
	new = split_rest2(new);
	cmd->line = new;
	cmd->split = ft_split(new, ' ');
	cmd->split = remake(cmd->split);
	return (1);
}

void parse_hook_split(t_cmd *cmd)
{
	int i = 0;
	int a = 0;
	int k = 0;
count_len(cmd);
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
	//while (cmd->split[i])
	//		printf("out = %d in =  %d rest = |%s|\n", cmd->out, cmd->in, cmd->split[i++]);
	//printf("id = %d  nbr = %d\n", cmd->id, env->nbr);
		i = 0;
	if (cmd->id == 1 && cmd->id != env->nbr)
	{
		cmd->out = 2;
	}
	if (cmd->id != 1 && cmd->id != env->nbr)
	{
		cmd->out = 2;
		cmd->in = 2;
	}
	if (cmd->id != 1 && cmd->id == env->nbr)
	{
		cmd->in = 2;
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
}

void parse_all(t_env *env)
{
    t_cmd *cmd;
    int i = 0;
    cmd = env->cmd;
	add_id(env);
	while (cmd)
    {
		remove_pipe_virgul(cmd);
		cmd->line = parse_dollars(cmd, env);
		parse_hook_split(cmd);
		check_in_out(cmd, env);
		create_fd(cmd);
		check_in_fd(cmd);

		//while (cmd->redi_in[i])
		//printf("out = %d in =  %d rest = |%s|\n", cmd->out, cmd->in, cmd->redi_in[i++]);
		i = 0;
		/*if (cmd->redi_out > 0)
		{
			while (cmd->redi_out[i])
				printf("redi = |%s|\n", cmd->redi_out[i++]);
		}
*/		cmd = cmd->next;
		i = 0;
    }
}

char *split_line(char *str)
{
	char *new;
	static int i =0;
	int a = i;
	if (str[i] == '\0')
	{
		i = 0;
		return (NULL);
	}

	while (str[i] && str[i] != ';')
	{
		while (str[i] == '"')
		{
			i++;
			while (str && str[i] != '"')
				i++;
			i++;
		}
		while (str[i] == '\'')
		{
			i++;
			while (str && str[i] != '\'')
				i++;
			i++;
		}
		if (str[i] != ';')
		i++;
	}
	new = ft_substr(str, a, i - a);
	if (str[i] != '\0')
		i++;
	return (new);
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
	env->envir = envir;
    while (1)
    {
	display_prompt();
    get_next_line(0, &line);
	while ((s_line = split_line(line)) != NULL)
	{
    	split_words(s_line, env);
    	parse_all(env);
		exec(env);
		//print(env->cmd);
		free_all(env);
	}
    }
}