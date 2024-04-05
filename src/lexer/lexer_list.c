/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2024/03/02 10:29:45 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	new_node2(t_lexer *new_node, int token)
{
	new_node->token = token;
	new_node->i = 0;
	new_node->next = NULL;
	new_node->prev = NULL;
}

int	new_node(char *str, int token, t_lexer **lexer_list)
{
	t_lexer	*new_node;
	t_lexer	*last_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (-1);
	new_node->str = NULL;
	new_node->str2 = NULL;
	if (str)
	{
		new_node->str = ft_strdup(str);
		new_node->str2 = ft_strdup(str);
	}
	new_node2(new_node, token);
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

int	token_checker(int i, char *s, t_lexer **lexer)
{
	int		trig;
	char	*tmp;

	trig = 0;
	if (che_tok(s[i], 0) != 0)
	{
		if (s[i + 1])
		{
			if ((che_tok(s[i], s[i + 1]) == 3 || che_tok(s[i], s[i + 1]) == 5)
				&& token_help(i, s, &trig, lexer) == -1)
				return (-1);
			if (che_tok(s[i], s[i + 1]) != 3 && che_tok(s[i], s[i + 1]) != 5
				&& che_tok(s[i + 1], 0) != 0)
			{
				tmp = syntax_error(che_tok(s[i + 1], 0));
				ft_err(NULL, tmp, NULL, 2);
				ft_free((void **)&tmp);
				lst_clear(lexer);
				return (-1);
			}
		}
		new_node(NULL, che_tok(s[i], s[i + 1]), lexer);
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
		if (str && i + tool->var->count < (int)ft_strlen(str)
			&& ft_isspace(str[i + tool->var->count]) == 1)
			return (sub(tool->var, lexer));
		if (str && i + tool->var->count < (int)ft_strlen(str)
			&& che_tok(str[i + tool->var->count], 0))
			return (sub(tool->var, lexer) - 1);
		if (i + tool->var->count < (int)ft_strlen(str))
			tool->var->count++;
	}
	sub(tool->var, lexer);
	return (tool->var->count);
}

t_lexer	*lexer(char *str, t_lexer *lexer, t_tool *tool)
{
	int	i;

	i = -1;
	tool->var = malloc(sizeof(t_var));
	if (tool->var == NULL)
		return (NULL);
	tool->var->str = str;
	while ((size_t)++i < ft_strlen(str))
	{
		tool->var->count = token_checker(i, str, &lexer);
		tool->var->i = i;
		i += len_word(i, str, &lexer, tool);
		if (i < 0)
			return (NULL);
	}
	if (begin_end(lexer) == NULL)
		return (NULL);
	lex_del(&lexer, 0, 0);
	if (lex_check_again(lexer) == -1)
		return (NULL);
	if (err_special_char(lexer, 0) == -1)
		return (NULL);
	return (lexer);
}
