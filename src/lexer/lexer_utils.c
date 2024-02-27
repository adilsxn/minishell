/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:19 by matilde           #+#    #+#             */
/*   Updated: 2024/02/27 12:12:57 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_spaces(char *str, int i)
{
	int	count;

	count = 0;
	while (ft_isspace(str[i + count]) == 1)
		count++;
	return (count);
}

int	len_quote(int i, char *str, char quote)
{
	int	count;

	count = 0;
	if (str != NULL && i + count < (int)ft_strlen(str) \
		&& str[i + count] == quote)
	{
		count++;
		while (str[i + count] != '\0' && str[i + count] != quote)
			count++;
		count++;
	}
	return (count);
}

t_token	che_tok(int c1, int c2)
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

char	*del_quote(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	reti(int trig)
{
	if (trig == 1)
		return (2);
	return (1);
}
