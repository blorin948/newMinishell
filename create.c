#include "minishell.h"

t_cmd *create_cmd(t_env *env)
{
    t_cmd *new;
    t_cmd *tmp;
    
    if (env->cmd == NULL)
    {
        if (!(new = init_cmd()))
            return (0);
        env->cmd = new;
    }
    else
    {
        if (!(new = init_cmd()))
            return (0);
        tmp = env->cmd;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = new;
        new->prev = tmp;
        new->next = NULL;
    }
    return (new);
}