/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2024/02/04 15:53:38 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	node_help(int in, t_tool *tool)
{
	if (tool->reset == 1)
	{
		in = 0;
		tool->reset = 0;
	}
	return (in);
}

int	new_node(char *str, int token, t_lexer **lexer_list, t_tool *tool)
{
	t_lexer		*new_node;
	t_lexer		*last_node;
	static int	in = 0;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (-1);
	new_node->str = NULL;
	if (str)
		new_node->str = ft_strdup(str);
	new_node->token = token;
	in = node_help(in, tool);
	new_node->i = in++;
	new_node->next = NULL;
	if (*lexer_list == NULL)
		*lexer_list = new_node;
	else
	{
		last_node = *lexer_list;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	return (0);
}

int	token_checker(int i, char *str, t_lexer **lexer, t_tool *tool)
{
	int	trig;

	trig = 0;
	if (check_token(str[i], 0) != 0)
	{
		if (str[i + 1])
		{
			if (check_token(str[i], str[i + 1]) == 3 \
				|| check_token(str[i], str[i + 1]) == 5)
			{
				if (token_help(i, str, &trig) == -1)
					return (-1);
			}
			else if (check_token(str[i + 1], 0) != 0)
			{
				ft_err("Double token", "Syntax error");
				return (-1);
			}
		}
		new_node(NULL, check_token(str[i], str[i + 1]), lexer, tool);
		if (trig == 1)
			return (2);
		return (1);
	}
	return (0);
}

int	len_word(int i, char *str, t_lexer **lexer, t_tool *tool)
{
	int		count;

	count = token_checker(i, str, lexer, tool);
	if (count > 0)
		return (count - 1);
	if (count == -1)
		return (-10000000);
	while (str[i + count] != '\0')
	{
		count += len_quote(i + count, str, 34);
		count += len_quote(i + count, str, 39);
		if (ft_isspace(str[i + count]) == 1)
			return (sub(str, i, count, lexer, tool));
		if (check_token(str[i + count], 0) != 0)
			return (sub(str, i, count, lexer, tool) - 1);
		if (str[i + count] != '\0')
			count++;
	}
	sub(str, i, count, lexer, tool);
	return (count);
}

t_lexer	*lexer(char *str, t_lexer *lexer, t_tool *tool)
{
	int	i;

	i = -1;
	while ((size_t)++i < ft_strlen(str))
	{
		i += len_word(i, str, &lexer, tool);
		if (i < 0)
			return (NULL);
	}
	if (lex_check(lexer) == NULL)
		return (NULL);
    lex_del(&lexer);
	return (lexer);
}
