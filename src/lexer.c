/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:31:32 by matilde           #+#    #+#             */
/*   Updated: 2023/09/11 12:29:26 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	count_spaces(char *str, int i)
{
	int	count;

	count = 0;
	while (is_whitespace(str[i + count]) == 1)
		count++;
	return (count);
}

int	len_quote(int i, char *str, char quote)
{
	int	count;

	count = 0;
	if (str[i + count] == quote)
	{
		count++;
		while (str[i + count] != quote && str[i + count] != '\0')
			count++;
		count++;
	}
	return (count);
}

t_tokens	check_token(int c1, int c2)
{
	if (c1 == '<' && c2 == '<')
		return (LESS_LESS);
	else if (c1 == '>' && c2 == '>')
		return (GREAT_GREAT);
	else if (c1 == '|')
		return (PIPE);
	else if (c1 == '>')
		return (GREAT);
	else if (c1 == '<')
		return (LESS);
	return (0);
}

int	len_word(int i, char *str, t_lexer **lexer_list)
{
	int	count;

	count = 0;
	while (str[i + count] != '\0' && check_token(str[i + count], 0) == 0)
	{
		count += len_quote(i + count, str, 34);
		count += len_quote(i + count, str, 39);
		if (is_whitespace(str[i + count]) == 1)
			break ;
		else
			count++;
	}
	if (add_lexer_node(ft_substr(str, i, count), 0, lexer_list) == -1)
		return (-1);
	return (count);
}
