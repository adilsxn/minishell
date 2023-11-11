/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:26:06 by matilde           #+#    #+#             */
/*   Updated: 2023/11/11 19:46:15 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/global.h"

int	minishell_loop(t_tool *tool)
{
	char	*tmp;
	size_t	count;

	count = -1;
	tool->arg = readline("minishell");
	tmp = ft_strtrim(tool->arg, " ");
	free(tool->arg);
	tool->arg = tmp;
	if (!tool->arg)
	{
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	if (tool->arg[0] == '\0')
	{
		reset_tool(tool);
		return (1);
	}
	if (count_quote(tool->arg) == 1)
		return (ft_error(2, tool));
	while (++count < ft_strlen(tool->arg))
	{
		count += len_word(count, tool->arg, &tool->lexer);
		if (count == 0)
			return (ft_error(1, tool));
	}
	parser(tool);
	g_global.in_cmd = 1;
	if (tool->pipes == 0)
		tool->simple_cmd = call_expander(tool, tool->simple_cmd);
	else
	{
		while (tool->simple_cmd)
		{
			tool->simple_cmd = call_expander(tool, tool->simple_cmd);
			if (tool->simple_cmd->next)
				tool->simple_cmd = tool->simple_cmd->next;
			else
				break ;
		}
	}
	g_global.in_cmd = 0;
	reset_tool(tool);
	return (1);
}

//minimum number of quotes has to be 2
//return the number to advance the str already checked
int	find_quote(char *line, int i, int *nb_quote, int quote)
{
	int	j;

	j = i + 1;
	*nb_quote += 1;
	while (line[j] && line[j] != quote)
		j++;
	if (line[j] == quote)
		*nb_quote += 1;
	return (j - i);
}

//if == 1 meaning no balanced number of quotes
//if == 0 meaning balanced number of quotes
int	count_quote(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_quote(line, i, &s, 39);
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (1);
	return (0);
}
