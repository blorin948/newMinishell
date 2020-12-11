#include "minishell.h"

t_cmd *init_cmd(void)
{
    t_cmd *new;
    if (!(new = malloc(sizeof(t_cmd))))
        return (NULL);
    new->next = NULL;
    new->prev = NULL;
    new->line = NULL;
    new->fd = 0;
    new->in = 0;
    new->out = 0;
	new->redi_out = NULL;
	new->out_len = 0;
	new->len = 0;
	new->in_len = 0;
	new->id = 0;
	new->pipefd = NULL;
	new->fd_in = 0;
	new->newpath = NULL;
	new->redi_in = NULL;
    return (new);
}

t_envir *init_envir(void)
{
	t_envir *new;
	if (!(new = malloc(sizeof(t_envir))))
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->name = NULL;
	new->content = NULL;
	return (new);
}

t_export *init_export(void)
{
	t_export *new;
	if (!(new = malloc(sizeof(t_export))))
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	return (new);
}
