/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilspt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:19 by matilde           #+#    #+#             */
/*   Updated: 2024/02/04 16:51:46 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	sub(char *str, int i, int count, t_lexer **lexer, t_tool *tool)
{
	char	*tmp;

	tmp = ft_substr(str, i, count);
	new_node(tmp, 0, lexer, tool);
	ft_free(tmp);
	return (count);
}

t_lexer	*lex_check(t_lexer *lexer)
{
	t_lexer	*lex;

	lex = lexer;
	while (lex->next)
		lex = lex->next;
	if (lex->token != 0 && lex->token != 1)
	{
		ft_err("Syntax error", "token at end of commands");
		return (NULL);
	}
	return (lexer);
}

void	lex_del(t_lexer **lexer)
{
	t_lexer	*lex;

	lex = *lexer;
	while (lex)
	{
		if (lex->str)
		{
			if (lex->str[0] == 0)
			{
				del_one(lexer, lex->i);
				lex = *lexer;
			}
		}
		lex = lex->next;
	}
}

int	token_help(int i, char *str, int *trig)
{
	*trig = 1;
	if (str[i + 2] && str[i + 3])
	{
		if (check_token(str[i + 2], str[i + 3] != 0))
		{
			ft_err("Double token", "Syntax error");
			return (-1);
		}
	}
	return (0);
}
