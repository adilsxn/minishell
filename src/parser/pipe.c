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

static int	has_pipe(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		if (lexer->token == PIPE)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

void	free_pipe(t_ppe *pipe)
{
	if (pipe == NULL)
		return ;
	free_pipe(pipe->next);
	free_cmd(pipe->cmd);
	ft_free(pipe);
}

static t_ppe	*mk_pipe(t_tool *data, t_ppe *prev)
{
	t_ppe	*proc;
	t_cmd	*cmd;

	cmd = mk_cmd(data);
	if (cmd == NULL)
		return (NULL);
	proc = ft_calloc(1, sizeof(t_ppe));
	if (proc == NULL)
		return (NULL);
	if (prev != NULL)
		prev->next = proc;
	proc->prev = prev;
	proc->cmd = cmd;
	return (proc);
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
	t_ppe	*pipeline;

	start = NULL;
	pipeline = NULL;
	if (has_pipe(data->lexer) == 0)
		return (NULL);
	while (pipeline != NULL)
	{
		pipeline = mk_pipe(data, pipeline);
		data->lexer = peek_pipe(data->lexer);
		if (pipeline == NULL)
		{
			free_pipe(start);
			return (NULL);
		}
		if (start == NULL)
			start = pipeline;
	}
	return (start);
}
