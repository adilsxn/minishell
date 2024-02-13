/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilspt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:19 by matilde           #+#    #+#             */
/*   Updated: 2024/02/12 21:19:59 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	sub(t_bitx *bix, t_lexer **lexer, t_tool *tool)
{
	char	*tmp;

	tmp = ft_substr(bix->str, bix->i, bix->count);
	new_node(tmp, 0, lexer, tool);
	ft_free((void **)&tmp);
	return (bix->count);
}

t_lexer	*lex_check(t_lexer *lexer)
{
	t_lexer	*lex;

	lex = lexer;
	while (lex->next)
		lex = lex->next;
	if (lex->token != 0 && lex->token != 1)
	{
		ft_err("Syntax error", "token at end of commands", NULL, 1);
		lst_clear(&lexer);
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

int	token_help(int i, char *str, int *trig, t_lexer **lexi)
{
	*trig = 1;
	if (str[i + 2] && str[i + 3])
	{
		if (check_token(str[i + 2], str[i + 3] != 0))
		{
			ft_err("Double token", "Syntax error", NULL, 1);
			lst_clear(lexi);
			return (-1);
		}
	}
	return (0);
}

int	lex_check_again(t_lexer *lex)
{
	t_lexer	*lexi;

	lexi = lex;
	while (lexi->next != NULL)
	{
		if (lexi->token != 0 && lexi->next->token != 0)
		{
			ft_err("Space between tokens or different tokens not allowed", \
				"Syntax error", NULL, 1);
			lst_clear(&lex);
			return (-1);
		}
		lexi = lexi->next;
	}
	return (0);
}
