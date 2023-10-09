/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:06:31 by matilde           #+#    #+#             */
/*   Updated: 2023/10/04 19:06:34 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	double_token_error(t_tool *tool)
{
	ft_putstr_fd("consecutive token found: ", 2);
	if (tool->lexer->token == GREAT)
		ft_putstr_fd("'>'\n", 2);
	else if (tool->lexer->token == GREAT_GREAT)
		ft_putstr_fd("'>>'\n", 2);
	else if (tool->lexer->token == LESS)
		ft_putstr_fd("'<'\n", 2);
	else if (tool->lexer->token == LESS_LESS)
		ft_putstr_fd("'<<'\n", 2);
	else if (tool->lexer->token == PIPE)
		ft_putstr_fd("'|'\n", 2);
	else
		ft_putstr_fd("\n", 2);
	lst_clear(&tool->lexer);
	reset_tool(tool);
	return (1);
}

int	ft_error(int error, t_tool *tool, t_lexer *lexer_list)
{
	lst_clear(&lexer_list);
	if (error == 0)
		ft_putstr_fd("lexer null error\n", 2);
	else if (error == 1)
		ft_putstr_fd("memory error: unable to assign memory\n", 2);
	else if (error == 2)
		ft_putstr_fd("syntax error: unable to locate closing quotation\n", 2);
	else if (error == 3)
		ft_putstr_fd("Parser problem\n", 2);
	else if (error == 4)
		ft_putstr_fd("Failed to create pipe\n", 2);
	else if (error == 5)
		ft_putstr_fd("Failed to fork\n", 2);
	else if (error == 6)
		ft_putstr_fd("outfile error\n", 2);
	else if (error == 7)
		ft_putstr_fd("infile: No such file or directory\n", 2);
	else if (error == 8)
		ft_putendl_fd("Path does not exist", 2);
	reset_tool(tool);
	return (1);
}

//if its a pipe, lexer isnt null
int	pipe_error(t_tool *tool)
{
	if (tool->lexer == NULL)
	{
		ft_error(0, tool, tool->lexer);
		return (1);
	}
	if (tool->lexer->token == PIPE)
	{
		double_token_error(tool);
		return (1);
	}
	return (0);
}