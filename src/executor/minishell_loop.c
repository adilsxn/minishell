/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:26:06 by matilde           #+#    #+#             */
/*   Updated: 2024/01/07 22:49:47 by matilde          ###   ########.fr       */
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
	{
		reset_tool(tool);
		return (1);
	}
	if (count_quote(tool->arg) == 1)
		return (ft_error(2, tool));
	if (minishell_loop2(tool) == 0)
		reset_tool(tool);
	return (1);
}

//heredoc already checks the redirection,
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
	printf("%s\n", tool->lexer->str);
	printf("%i\n", tool->lexer->token);
	printf("%s\n", tool->lexer->next->next->str);
	parser(tool);
	if (tool->pipes == 0)
	{
		tool->simple_cmd = call_expander(tool, tool->simple_cmd);
		send_heredoc(tool, tool->simple_cmd);
		if (tool->simple_cmd->redirect != NULL)
			if (check_redirect(tool->simple_cmd) == 1)
				exit(1);
	}
	else
		minishell_loop3(tool);
	return (0);
}

void	minishell_loop3(t_tool *tool)
{
	int	fd_in;
	int	end[2];

	while (tool->simple_cmd)
	{
		tool->simple_cmd = call_expander(tool, tool->simple_cmd);
		send_heredoc(tool, tool->simple_cmd);
		if (tool->simple_cmd->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(tool, end, tool->simple_cmd);
		if (tool->simple_cmd->next)
			tool->simple_cmd = tool->simple_cmd->next;
		else
			break ;
	}
	tool->simple_cmd = first_simple_cmd(tool->simple_cmd);
}
