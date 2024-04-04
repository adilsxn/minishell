/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:12:20 by matilde           #+#    #+#             */
/*   Updated: 2024/04/04 12:50:12 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quotes(t_lexer *lex, int i, int *count1, int *count2)
{
	if (lex->str[i] == 34)
		*count1 += 1;
	else if (lex->str[i] == 39)
		*count2 += 1;
}

int	unclosed_quotes(t_lexer *lexi, int i, int count1, int count2)
{
	t_lexer	*lex;

	lex = lexi;
	while (lex)
	{
		i = 0;
		if (lex->str)
		{
			i += len_quote(0, lex->str, 34);
			i += len_quote(0, lex->str, 39);
			while (i < (int)ft_strlen(lex->str))
			{
				quotes(lex, i, &count1, &count2);
				i++;
			}
		}
		lex = lex->next;
	}
	if (count1 % 2 != 0 || count2 % 2 != 0)
	{
		ft_err(NULL, "syntax error near unexpected token `newline'", NULL, 2);
		return (-1);
	}
	else
		return (0);
}

int	special_char(t_lexer *lex, int i, t_lexer *lexi)
{
	if (lex->str[i] == ';')
	{
		ft_err(NULL, "syntax error near unexpected token `;'", NULL, 2);
		lst_clear(&lexi);
		return (-1);
	}
	else if (lex->str[i] == 92)
	{
		ft_err(NULL, "syntax error near unexpected token `\\'", NULL, 2);
		lst_clear(&lexi);
		return (-1);
	}
	return (0);
}

int	err_special_char(t_lexer *lexi, int i)
{
	t_lexer	*lex;

	lex = lexi;
	while (lex)
	{
		i = 0;
		if (lex->str)
		{
			i += len_quote(0, lex->str, 34);
			i += len_quote(0, lex->str, 39);
			while (i < (int)ft_strlen(lex->str))
			{
				if (special_char(lex, i, lexi) == -1)
					return (-1);
				i++;
			}
		}
		lex = lex->next;
	}
	i = unclosed_quotes(lexi, 0, 0, 0);
	if (i == -1)
		lst_clear(&lexi);
	return (i);
}

void	printin(t_lexer *lex)
{
	t_lexer	*lexi;

	lexi = lex;
	printf("------printin---------\n");
	while (lexi)
	{
		if (lexi->str)
			printf("str: .%s.\n", lexi->str);
		if (lexi->token)
			printf("token: %d\n", lexi->token);
		if (lexi->i)
			printf("i: %d\n", lexi->i);
		lexi = lexi->next;
	}
	printf("------printin---------\n");
}
