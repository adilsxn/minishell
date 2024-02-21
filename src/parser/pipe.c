/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:12:32 by matilde           #+#    #+#             */
/*   Updated: 2024/01/08 19:10:15 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	has_pipe(t_lexer *lexer)
{
    t_lexer *it;

    it = lexer;
	while (it != NULL)
	{
		if (it->token == PIPE)
			return (1);
		it = it->next;
	}
	return (0);
}

static t_ppe	*mk_pipe(t_lexer *lexer, t_env *env, t_ppe *prev)
{
    t_ppe	*proc;
    t_cmd	*cmd;

    cmd = mk_cmd(lexer, env);
    if (cmd == NULL)
        return (NULL);
    proc = ft_calloc(1, sizeof(t_ppe));
    if (proc == NULL)
    {
        ft_free((void **)&cmd);
        return (NULL);
    }
    if (prev != NULL)
        prev->next = proc;
    proc->prev = prev;
    proc->cmd = cmd;
    return (proc);
}

void	free_pipe(t_ppe **pipe)
{
    t_ppe *it;
    t_ppe *tmp;

    it = *pipe;
    tmp = NULL;
    while (it != NULL)
    {
        tmp = it->next;
        free_cmd(&(it->cmd));
        ft_free((void **)&it);
        it = tmp;
    }
    *pipe = NULL;
}

static t_lexer	*peek_pipe(t_lexer *lexer)
{
	t_lexer *it;

	it = lexer;
	while (it != NULL)
	{
		if (it->token == PIPE)
			return (it->next);
		it = it->next;
	}
	return (NULL);
}

t_ppe	*parser(t_tool *data)
{
	t_ppe	*start;
    t_ppe   *pipeline;
    t_lexer *it;

	start = NULL;
	pipeline = NULL;
    it = data->lexer;
	while (it != NULL)
	{
		pipeline = mk_pipe(it, data->env, pipeline);
		it = peek_pipe(it);
		if (pipeline == NULL)
		{
			free_pipe(&start);
			return (NULL);
		}
		if (start == NULL)
			start = pipeline;
	}
	return (start);
}
