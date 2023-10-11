/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:03:23 by matilde           #+#    #+#             */
/*   Updated: 2023/10/11 12:31:53 by matilde          ###   ########.fr       */
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
		if (is_whitespace(str[i + count]) == 1)
			break ;
		else
			count++;
	}
	if (check_token(str[i + count], 0) != 0)
		new_node(NULL, check_token(str[i + count], str[i + count +1]), lexer);
	else
		new_node(ft_substr(str, i, count), 0, lexer);
	if (check_token(str[i + count], str[i + count +1]) == LESS
		|| check_token(str[i + count], str[i + count +1]) == GREAT)
		count = 1;
	else if (check_token(str[i + count], 0) != 0)
		count = 2;
	return (count);
}
