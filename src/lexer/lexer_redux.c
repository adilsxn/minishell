/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 22:31:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/04/04 14:59:40 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	renumber(t_lexer **lst)
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
			it->str2 = it->next->str2;
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

void	quote_help(t_lexer *shell)
{
	t_lexer	*le;

	le = shell;
	while (le)
	{
		if (le->str)
		{
			if (ft_strequ(le->str, "echo"))
			{
				if (quote_assist(le->str, 34) < 2)
					le->str = del_quote(le->str, 39);
				else if (quote_assist(le->str, 39) < 2)
					le->str = del_quote(le->str, 34);
			}
			else if (le->str[0] == 34 && le->str[1] == 34 && ft_strequ(le->str
					+ 2, "echo"))
				le->str = del_quote(le->str, 34);
			if (quote_assist(le->str, 34) < 2)
				le->str = del_quote(le->str, 39);
			else if (quote_assist(le->str, 39) < 2)
				le->str = del_quote(le->str, 34);
		}
		le = le->next;
	}
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
