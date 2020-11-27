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
    return (new);
}

