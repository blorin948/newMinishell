#include "minishell.h"

void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int ft_strcmp(char *str1, char *str2)
{
	int i = 0;
	if (str1 == NULL || str2 == NULL)
		return (-1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}