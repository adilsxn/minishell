/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2024/01/04 20:29:20 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	new_node(char *str, int token, t_lexer **lexer_list)
{
	t_lexer		*new_node;
	t_lexer		*last_node;
	static int	i = 0;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_node)
		return (-1);
	new_node->str = str;
	new_node->token = token;
	new_node->i = i++;
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

int	len_word(int i, char *str, t_lexer **lexer)
{
	int	count;

	count = 0;

	while (str[i + count] != '\0' && check_token(str[i + count], 0) == 0)
	{
		count += len_quote(i + count, str, 34);
		count += len_quote(i + count, str, 39);
		if (ft_isspace(str[i + count]) == 1)
			break ;
		if (str[i + count] != '\0')
			count++;
	}
	if (check_token(str[i + count], 0) != 0)
		new_node(NULL, check_token(str[i + count], str[i + count +1]), lexer);
	else
		new_node(ft_substr(str, i, count), 0, lexer);
	if (check_token(str[i + count], 0) == PIPE)
		return (1);
	if ((i + count + 1) < (int)ft_strlen(str))
		if (check_token(str[i + count], str[i + count +1]) == LESS \
			|| check_token(str[i + count], str[i + count +1]) == GREAT)
			return (1);
	if (check_token(str[i + count], 0) != 0)
		return (2);
	return (count);
}

t_lexer	*lexer(char *str, t_lexer *lexer, t_tool *tool)
{
	int i;
	t_lexer *lexi;

	i = -1;
	while ((size_t)++i < ft_strlen(str))
	{
		i += len_word(i, str, &lexer);
		if (i == 0)
		{
			ft_error(1, tool);
			return NULL;
		}
	}
	lexi = lexer;
	while (lexer)
	{
		printf("lexer: %s\n", lexer->str);
		lexer = lexer->next;
	}
	lexer = lexi;
	free(str);
	return (lexer);
}
