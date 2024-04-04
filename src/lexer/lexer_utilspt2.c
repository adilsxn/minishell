/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilspt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:19 by matilde           #+#    #+#             */
/*   Updated: 2024/04/03 18:45:24 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	sub(t_var *var, t_lexer **lexer)
{
	char	*tmp;

	tmp = ft_substr(var->str, var->i, var->count);
	new_node(tmp, 0, lexer);
	ft_free((void **)&tmp);
	return (var->count);
}

t_lexer	*begin_end(t_lexer *lexer)
{
	t_lexer	*lex;
	char	*tmp;

	lex = lexer;
	if (lex && lex->token && lex->token == 1)
	{
		tmp = syntax_error(lex->token);
		ft_err(NULL, tmp, NULL, 2);
		ft_free((void **)&tmp);
		lst_clear(&lexer);
		return (NULL);
	}
	while (lex && lex->next)
		lex = lex->next;
	if (lex && lex->token != 0)
	{
		tmp = syntax_error(lex->token);
		ft_err(NULL, tmp, NULL, 2);
		ft_free((void **)&tmp);
		lst_clear(&lexer);
		return (NULL);
	}
	return (lexer);
}

void	lex_del(t_lexer **lexer, int i, int j)
{
	t_lexer	*lex;
	t_lexer	*next_lex;
	t_lexer	*lexi;

	lex = *lexer;
	lexi = *lexer;
	while (lexi)
	{
		i++;
		lexi = lexi->next;
	}
	lexer_redux(lexer);
	while (lex != NULL)
	{
		next_lex = lex->next;
		if (ft_strlen(lex->str) == 0 && lex->token == 0)
		{
			j++;
			del_one(lexer, lex->i);
		}
		lex = next_lex;
	}
}

int	token_help(int i, char *str, int *trig, t_lexer **lexi)
{
	char	*tmp;

	*trig = 1;
	if (str[i + 2] && str[i + 3])
	{
		if (che_tok(str[i + 2], str[i + 3]) != 0)
		{
			tmp = syntax_error(che_tok(str[i + 2], str[i + 3]));
			ft_err(NULL, tmp, NULL, 2);
			ft_free((void **)&tmp);
			lst_clear(lexi);
			return (-1);
		}
	}
	return (0);
}

int	lex_check_again(t_lexer *lex)
{
	char	*tmp;
	t_lexer	*lexi;

	lexi = lex;
	while (lexi && lexi->next != NULL)
	{
		if (lexi->token != 0 && lexi->next->token != 0)
		{
			if (lexi->token == 1 && lexi->next->token == 2)
			{
				lexi = lexi->next;
				continue ;
			}
			else
			{
				tmp = syntax_error(lexi->token);
				ft_err(NULL, tmp, NULL, 2);
				ft_free((void **)&tmp);
				lst_clear(&lex);
				return (-1);
			}
		}
		lexi = lexi->next;
	}
	return (0);
}
