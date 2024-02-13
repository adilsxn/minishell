/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:31:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/12 21:57:57 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	renumber(t_lexer **lst)
{
	int		i;
	t_lexer	*it;

	i = 0;
	it = *lst;
	while (it != NULL)
	{
		it->i = i;
		it = it->next;
		i++;
	}
}

void	lexer_redux(t_lexer **lexer)
{
	t_lexer	*it;
	t_lexer	*del;

	it = *lexer;
	del = NULL;
	while (it != NULL && it->next != NULL)
	{
		if (it->token > 1)
		{
			it->str = it->next->str;
			del = it->next;
			it->next = del->next;
			if (del->next != NULL)
				del->next->prev = it;
			ft_free((void **)&del);
		}
		it = it->next;
	}
	renumber(lexer);
}

int	node_help(int in, t_tool *tool)
{
	if (tool->reset == 1)
	{
		in = 0;
		tool->reset = 0;
	}
	return (in);
}

void	quote_help(t_lexer *shell)
{
	t_lexer	*le;
	int		a;

	a = 1;
	le = shell;
	while (le)
	{
		if (le->str)
		{
			if (ft_strequ(shell->str, "echo"))
			{
				if (quote_assist(le->str, 34) < 2)
					le->str = del_quote(le->str, 39);
				else if (quote_assist(le->str, 39) < 2)
					le->str = del_quote(le->str, 34);
			}
			else if (le->str[0] == 34 && le->str[1] == 34)
				a = 0;
			else
				le->str = del_quote(le->str, 34);
		}
		le = le->next;
	}
	(void)a;
}

int	quote_assist(char *str, int q)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == q)
			a = 1;
		i++;
		if (str[i] && str[i] == q && a == 1)
			return (2);
	}
	return (a);
}
