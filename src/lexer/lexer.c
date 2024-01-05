/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:34:33 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/28 16:34:33 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../../inc/minishell.h>

t_lexer lexer(char *input)
{
	int currPos;
	int nextPos;

	currPos = 0;
	nextPos = 0;
	input = ft_strtrim(input, " ");

	while (input[currPos] != NULL)
	{
		while(input[currPos] == ' ')
		{
			currPos++;
			nextPos = currPos;
		}
		if (input[currPos] == '|')
			return ((t_lexer){PIPE, "|", 0, NULL, NULL});
		if (input[currPos] == '>' && input[currPos + 1] != '>')
			return ((t_lexer){GREAT, ">", 0, NULL, NULL});
		if (input[currPos] == '>' && input[currPos + 1] == '>')
			return ((t_lexer){GREAT_GREAT, ">>", 0, NULL, NULL});
		if (input[currPos] == '<' && input[currPos + 1] != '<')
			return ((t_lexer){LESS, "<", 0, NULL, NULL});
		if (input[currPos] == '<' && input[currPos + 1] == '<')
			return ((t_lexer){LESS_LESS, "<<", 0, NULL, NULL});
		else
			return ((t_lexer){WOR, "<<", 0, NULL, NULL});
	}
}
}
