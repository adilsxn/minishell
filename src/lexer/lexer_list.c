/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2024/02/14 15:03:04 by matilde          ###   ########.fr       */
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
				if (token_help(i, str, &trig, lexer) == -1)
					return (-1);
			}
			else if (check_token(str[i + 1], 0) != 0)
			{
				ft_err("Double token", "Syntax error", NULL, 1);
				lst_clear(lexer);
				return (-1);
			}
		}
		new_node(NULL, check_token(str[i], str[i + 1]), lexer, tool);
		return (reti(trig));
	}
	return (0);
}

int	len_word(int i, char *str, t_lexer **lexer, t_tool *tool)
{
	if (tool->var->count > 0)
		return (tool->var->count - 1);
	if (tool->var->count == -1)
		return (-10000000);
	while (i + tool->var->count < (int)ft_strlen(str))
	{
		tool->var->count += len_quote(i + tool->var->count, str, 34);
		tool->var->count += len_quote(i + tool->var->count, str, 39);
		if (str && i + tool->var->count < (int)ft_strlen(str) \
			&& ft_isspace(str[i + tool->var->count]) == 1)
			return (sub(tool->var, lexer, tool));
		if (str && i + tool->var->count < (int)ft_strlen(str) \
			&& check_token(str[i + tool->var->count], 0))
			return (sub(tool->var, lexer, tool) - 1);
		if (i + tool->var->count < (int)ft_strlen(str))
			tool->var->count++;
	}
	sub(tool->var, lexer, tool);
	return (tool->var->count);
}

t_lexer	*lexer(char *str, t_lexer *lexer, t_tool *tool)
{
	int		i;

	i = -1;
	tool->var = malloc(sizeof(t_var));
	if (tool->var == NULL)
		return (NULL);
	tool->var->str = str;
	while ((size_t)++i < ft_strlen(str))
	{
		tool->var->count = token_checker(i, str, &lexer, tool);
		tool->var->i = i;
		i += len_word(i, str, &lexer, tool);
		if (i < 0)
			return (NULL);
	}
	if (lex_check(lexer) == NULL)
		return (NULL);
	lex_del(&lexer);
	if (lex_check_again(lexer) == -1)
		return (NULL);
	return (lexer);
}
