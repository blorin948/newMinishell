
#include "minishell.h"

void print(t_cmd *cmd)
{
    int i = 0;

    while (cmd->next)
    {
    //    printf("%s in = %d  out = %d  len = %d\n", cmd->line, cmd->in, cmd->out, cmd->len);
        cmd = cmd->next;
    }
	printf("%s in = %d  out = %d len = %d\n", cmd->line, cmd->in, cmd->out, cmd->len);
	if (cmd->redi_out)
	{
	char **tab = cmd->split;
	while (tab[i])
		printf("|%s|\n", tab[i++]);
	}
}


void display_prompt(void)
{
    ft_putstr_fd("prompteur : ", 1);
}

int line_cpy(t_cmd *cmd, char *line, int end, int start)
{
    char *new;
    int i = 0;

    if (!(cmd->line = malloc(sizeof(char) * end - start + 1)))
        return (0);
	if (line[end] == '|')
	{
    	while (start <= end)
    	{
        	cmd->line[i] = line[start];
        	start++;
     	   i++;
    	}
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
        	cmd->line[i] = line[start];
        	start++;
     	   i++;
    	}
	}
	
    cmd->line[i] = '\0'; 
}

void split_words(char *line, t_env *env)
{
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
        if ((line[i] == '|' || line[i] == ';') && cro == 0 && guill == 0)
        {
            end = i;
            line_cpy(create_cmd(env), line, end, start);
            start = end;
        }
        i++;
    }
    end = i;
    line_cpy(create_cmd(env), line, end, start);
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
		cmd->in = 2;
	if (cmd->line[ft_strlen(cmd->line) - 1] == '|')
		cmd->out = 2;
	cmd->line = remove_pipe2(cmd->line, cmd->in, cmd->out, ft_strlen(cmd->line));
	if (cmd->line[0] == ';')
		before = 1;
	if (cmd->line[ft_strlen(cmd->line) - 1] == ';')
		after = 1;
	cmd->line = remove_virgul2(cmd->line, before, after, ft_strlen(cmd->line));

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
      exit ;
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
    exit ;
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
			printf("test\n");
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
	if (!(tab = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (line[i] && line[i] == redir)
	{
		tab[a] = line[i];
		i++;
		a++;
	}
	while (line[i] && line[i] == ' ')
	{
		tab[a] = line[i];
		i++;
		a++;
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

char **create_tab_redir(t_cmd *cmd, int len, char redir)
{
	char **tab;
	char *new = cmd->line;
	int i = 0;
	int a = 0;
	int k = 0;
	int cro = 0;
	int guill = 0;
	if (!(tab = malloc(sizeof(char *) * len)))
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
			k = count_len2(new, i);
			tab[a] = fill_tab(new, i, k, redir);
			a++;
			i = i + k - 1;
		}
		i++;
	}
	tab[a] = 0;
	return (tab);
}

int copy_redir(t_cmd *cmd)
{
	if (cmd->out_len != 0)
		cmd->redi_out = create_tab_redir(cmd, cmd->out_len, '>');
	if (cmd->in_len != 0)
		cmd->redi_in = create_tab_redir(cmd, cmd->in_len, '<');
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
		if (line[i] == '>' || line[i] == '<')
		{
			i = i + count_len2(line, i);
		}
		new[a++] = line[i++];
	}
	new[a] = '\0';
	//cmd->line = new;
	new = split_rest2(new);
	cmd->line = new;
	cmd->split = ft_split(new, ' ');
	cmd->split = remake(cmd->split);

}

char **parse_hook_split(t_cmd *cmd)
{
	int i = 0;
	int a = 0;
	int k = 0;
	count_len(cmd);
	copy_redir(cmd);
	split_rest(cmd);
}

int parse_all(t_env *env)
{
    t_cmd *cmd;
    int i = 0;
	i = TRUE;
    cmd = env->cmd;
    while (cmd)
    {
		remove_pipe_virgul(cmd);
		cmd->line = parse_dollars(cmd, env);
		cmd->split = parse_hook_split(cmd);
		cmd = cmd->next;
    }
}

int     main(int ac, char **av, char **envir)
{
    char *line = NULL;
    t_env *env;
	int i = 0;
    if (!(env = malloc(sizeof(t_env))))
        return (0);

	env->envir = envir;
    while (1)
    {

    display_prompt();
    get_next_line(0, &line);
    split_words(line, env);
    parse_all(env);
	print(env->cmd);
    return (0);
    }
}