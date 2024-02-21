/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 23:03:18 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/05 23:03:18 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_rdr(t_rdr **rdir)
{
	t_rdr	*it;
	t_rdr	*tmp;

	it = *rdir;
	tmp = NULL;
	while (it != NULL)
	{
		tmp = it->next;
        free(it->value);
		ft_free((void **)&it);
		it = tmp;
	}
}

static t_rdr	*mk_rdr(t_lexer *lexer, t_env *env, t_rdr *prev)
{
	t_rdr	*rdir;
	int		ret;

	ret = 0;
	rdir = ft_calloc(1, sizeof(t_rdr));
	if (rdir == NULL)
		return (NULL);
	rdir->value = ft_strdup(lexer->str);
	if (lexer->token == GREAT)
		ret = handle_output(rdir);
	else if (lexer->token == LESS)
		ret = handle_input(rdir);
	else if (lexer->token == GREAT_GREAT)
		ret = handle_append(rdir);
	else
		ret = handle_heredoc(lexer, env, rdir);
	if (prev != NULL)
		prev->next = rdir;
	if (ret == -1)
		return (free_rdr(&rdir), NULL);
	return (rdir);
}

t_rdr	*build_rdr(t_lexer *lexi, t_cmd *cmd, t_env *env)
{
	t_rdr	*start;
	t_rdr	*rdir;
	t_lexer	*it;

	start = NULL;
	rdir = NULL;
	it = lexi;
	while (it != NULL && it->token != PIPE)
	{
		if (it->token > PIPE)
		{
			cmd->io = true;
			rdir = mk_rdr(it, env, rdir);
			if (start == NULL)
				start = rdir;
            if (rdir == NULL)
                return (free_rdr(&start), NULL);
		}
		it = it->next;
	}
	return (start);
}
