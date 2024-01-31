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

void	free_rdr(t_rdr *rdir)
{
	if (rdir == NULL)
		return ;
	free_rdr(rdir->next);
	ft_free(rdir);
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

t_rdr	*build_rdr(t_lexer *lexi)
{
	t_rdr	*start;
	t_rdr	*rdir;
	t_lexer *it;

	start = NULL;
	rdir = NULL;
	it = lexi;
	while (it != NULL && it->token != PIPE)
	{
		if (it->token == GREAT || it->token == LESS
			|| it->token == GREAT_GREAT || it->token == LESS_LESS)
		{
			rdir = mk_rdr(it->token, rdir);
			if (rdir == NULL)
			{
				free_rdr(start);
				return (ft_err("redirection", NULL), NULL);
			}
			if (start == NULL)
				start = rdir;
			rdir->value = it->next->str;
		}
		it = it->next;
	}
	return (start);
}
