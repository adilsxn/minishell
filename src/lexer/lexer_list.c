/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2024/01/25 15:38:06 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (tool->reset == 1)
		in = 0;
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
		if (check_token(str[i], str[i + 1]) == 3 \
			|| check_token(str[i], str[i + 1]) == 5)
		{
			trig = 1;
			if (check_token(str[i + 2], str[i + 3] != 0))
			{
				ft_err("Double token", "Syntax error");
				return (-1);
			}
		}
		else
		{
			if (check_token(str[i + 1], 0) != 0)
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
	char	*tmp;

	count = token_checker(i, str, lexer, tool);
	tmp = NULL;
	if (count > 0)
		return (count - 1);
	if (count == -1)
		return (count);
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
	tmp = ft_substr(str, i, count);
	new_node(tmp, 0, lexer, tool);
	ft_free(tmp);
	return (count);
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

t_lexer	*lexer(char *str, t_lexer *lexer, t_tool *tool)
{
	int	i;

	i = -1;
	while ((size_t)++i < ft_strlen(str))
	{
		if (len_word(i, str, &lexer, tool) != -1)
			i += len_word(i, str, &lexer, tool);
		else
		{
			if (str)
				free(str);
			return (NULL);
		}
		if (i == 0)
		{
			if (str)
				free(str);
			ft_err("Invalid Commands", "in lexer");
			return (NULL);
		}
	}
	free(str);
	if (lex_check(lexer) == NULL)
		return (NULL);
	lex_del(&lexer);
	return (lexer);
}
