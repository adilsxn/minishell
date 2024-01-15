/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:26:06 by matilde           #+#    #+#             */
/*   Updated: 2024/01/15 20:35:52 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//readline dynamically allocates memory for each input, so free after
//trim to remove spaces from begining and end
//if the entire pointer tool->arg is NULL, exit
//if the first char of the str pointed to by tool->arg is the null character,
//ask for another arg
//when press Enter on the terminal without entering any other char
//the input buffer is an empty string ("")
int	minishell_loop(t_tool *tool)
{
	char	*tmp;

	tool->arg = readline("minishell: ");
	tmp = ft_strtrim(tool->arg, " ");
	free(tool->arg);
	tool->arg = tmp;
	if (!tool->arg)
	{
		ft_putendl_fd("exit", 2);
		exit(0);
	}
	if (tool->arg[0] == '\0')
		return (reset_tool(tool), 1);
	add_history(tool->arg);
	if (count_quote(tool->arg) == 1)
		return (ft_error(2, tool));
	if (minishell_loop2(tool) == 0)
		reset_tool(tool);
	return (1);
}

//heredoc already checks the redirection,
//which heredoc ?
//so if theres another redirection its an error
int	minishell_loop2(t_tool *tool)
{
	size_t	count;

	count = -1;
	while (++count < ft_strlen(tool->arg))
	{
		count += len_word(count, tool->arg, &tool->lexer);
		if (count == 0)
			return (ft_error(1, tool));
	}
    t_lexer *i;
    while (i != NULL)
	parser(tool);
	if (tool->pipes == 0)
	{
		// what exactly happens here ?
		tool->simple_cmd = call_expander(tool, tool->simple_cmd);
		// what exactly happens here ?
		send_heredoc(tool, tool->simple_cmd);
		if (tool->simple_cmd->redirect != NULL)
		// what exactly happens here ?
			if (check_redirect(tool->simple_cmd) == 1)
				exit(1);
	}
	else
	// what is this function doing ?
		minishell_loop3(tool);
	return (0);
}
// what is this function doing ?
void	minishell_loop3(t_tool *tool)
{
	int	fd_in;
	int	end[2];

	while (tool->simple_cmd)
	{
		// why are we calling this function ?
		tool->simple_cmd = call_expander(tool, tool->simple_cmd);
		// why are we calling this function ?
		send_heredoc(tool, tool->simple_cmd);
		if (tool->simple_cmd->prev)
			close(fd_in);
		// what is this function doing ?
		fd_in = check_fd_heredoc(tool, end, tool->simple_cmd);
		if (tool->simple_cmd->next)
			tool->simple_cmd = tool->simple_cmd->next;
		else
			break ;
	}
	// what is happening here ?
	tool->simple_cmd = first_simple_cmd(tool->simple_cmd);
}
