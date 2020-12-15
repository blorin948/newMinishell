#include "minishell.h"

int is_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*fill_export2(char *str, int i)
{
	char *new;
	int a;
	int c;

	a = 0;
	c = 0;
	if (is_char(str, '=') > 0)
		new = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	else
		new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '=' && c == 0 && (c += 1))
		{
			new[a++] = str[i++];
			new[a++] = '"';
		}
		else
			new[a++] = str[i++];
	}
	if (c > 0)
		new[a++] = '"';
	new[a] = '\0';
	return (new);
}

int is_already(t_export *export, char *str)
{
	int i = 0;
	while (export)
	{
		if (ft_strcmp(export->name, str) == 0)
			return (1);
		export = export->next;
	}
	return (0);
}

int is_already_envir(t_envir *envir, char *str)
{
	int i = 0;
	while (envir)
	{
		if (ft_strcmp(envir->name, str) == 0)
			return (1);
		envir = envir->next;
	}
	return (0);
}
