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

static bool control_for_null(t_rdr *redir, t_rdr **start, t_lexer *it)
{
	if (*start == NULL)
        *start = redir;
    redir->value = it->str;
    if (redir->kind == RDR_OUT || redir->kind == RDR_APP)
    {
        if (ft_strequ("\"\"", redir->value) == 1 || !(redir->value))
        {
            free_rdr(start);
            return (ft_err(" ", "No such file or directory", NULL, 1), true);
        }
    }
    return (false);
}

void	free_rdr(t_rdr **rdir)
{
    t_rdr *it;
    t_rdr *tmp;

    it = *rdir;
    tmp = NULL;
    while (it != NULL)
    {
        tmp = it->next;
        ft_free(it);
        it = tmp;
    }
}

static t_rdr	*mk_rdr(t_token type, t_rdr *prev)
{
	t_rdr	*rdir;

	rdir = ft_calloc(1, sizeof(t_rdr));
	if (rdir == NULL)
		return (NULL);
	if (type == GREAT)
		rdir->kind = RDR_OUT;
	else if (type == LESS)
		rdir->kind = RDR_IN;
	else if (type == GREAT_GREAT)
		rdir->kind = RDR_APP;
	else
		rdir->kind = RDR_HD;
	if (prev != NULL)
		prev->next = rdir;
	return (rdir);
}

t_rdr	*build_rdr(t_lexer *lexi, t_cmd *cmd)
{
	t_rdr	*start;
	t_rdr	*rdir;
	t_lexer	*it;

	start = NULL;
	rdir = NULL;
	it = lexi;
	while (it != NULL && it->token != PIPE)
	{
		if (it->token == GREAT || it->token == LESS || it->token == GREAT_GREAT
			|| it->token == LESS_LESS)
		{
            cmd->io = true;
			rdir = mk_rdr(it->token, rdir);
			if (rdir == NULL)
			{
				free_rdr(&start);
				return (ft_err("redirection", NULL, NULL, 1), NULL);
			}
            if (control_for_null(rdir, &start, it) == true)
                return (NULL);
		}
		it = it->next;
	}
	return (start);
}
