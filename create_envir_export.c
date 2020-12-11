#include "minishell.h"

char *find_name(char *str)
{
	char *new;
	int i = 0;
	int a = 0;
	if ((!str) && ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	i--;
	if (!(new = malloc(sizeof(char) * i + 1)))
		return (NULL);
	a = i + 1;
	i = 0;
	while (i < a)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char *find_content(char *str)
{
	char *new;
	int i = 0;
	int a = 0;
	if ((!str) && ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	a = i;
	while (str[i])
		i++;
	if (!(new = malloc(sizeof(char) * i - a + 1)))
		return (NULL);
	i = 0;
	while (str[a])
	{
		new[i++] = str[a++];
	}
	new[i] = '\0';
	return (new);
}

void fill_export(t_export *export, char *str)
{
	int i = 0;
	int a = 0;
	while (str[i])
	{
		if (str[i] == '=')
			a++;
		i++;
	}
	if (a > 0)
	{
		if (!(export->str = malloc(sizeof(char) * ft_strlen(str) + 3)))
			return ;

	}
	else
	{
		if (!(export->str = malloc(sizeof(char) * ft_strlen(str) + 1)))
			return ;
	}
	a = 0;
	i = 0;
	int c = 0;
	while (str[i])
	{
		if (str[i] == '=' && c == 0)
		{
			export->str[a++] = str[i++];
			export->str[a++] = '"';
			c++;
		}
		else
			export->str[a++] = str[i++];
	}
	if (c > 0)
		export->str[a++] = '"';
	export->str[a] = '\0';
}

void fill_envir(t_envir *envir, char *str)
{
	envir->str = str;
	envir->name = find_name(str);
	envir->content = find_content(str);
}

void create_envir_export(t_env *env, char **tab)
{
	int i = 0;
	while (tab[i])
	{
		fill_envir(create_envir(env), tab[i]);
		fill_export(create_export(env), ft_strjoin("declare -x ", tab[i]));
		i++;
	}
}
