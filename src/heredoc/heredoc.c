/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:08:30 by matilde           #+#    #+#             */
/*   Updated: 2023/11/27 19:01:24 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//if delimitor doesnt have quotes, do expander
//heredoc->str is the delimitor
//if line is NULL after the free means readline failed or reached end of input
int	create_heredoc(t_lexer *heredoc, bool quote, t_tool *tool, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str) != 0))
	{
		if (quote == false)
			line = expander_str(tool, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (!line)
		return (1);
	close(fd);
	return (0);
}

//check if delimitor has quotes, and eliminate them
int	ft_heredoc(t_tool *tool, t_lexer *heredoc, char *file)
{
	bool	quote;
	int		trig;

	trig = 0;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quote = true;
	else
		quote = false;
	del_quote(heredoc->str, '\"');
	del_quote(heredoc->str, '\'');
	trig = create_heredoc(heredoc, quote, tool, file);
	tool->heredoc = true;
	return (trig);
}

int	send_heredoc(t_tool *tool, t_simple_cmd *cmd)
{
	t_lexer	*start;

	start = cmd->redirect;
	while (cmd->redirect)
	{
		if (cmd->redirect->token == LESS_LESS)
		{
			if (cmd->hd_file)
				free(cmd->hd_file);
			cmd->hd_file = create_hd_file();
			if (ft_heredoc(tool, cmd->redirect, cmd->hd_file) == 1)
			{
				reset_tool(tool);
				return (1);
			}
		}
		cmd->redirect = cmd->redirect->next;
	}
	cmd->redirect = start;
	return (0);
}

char	*create_hd_file(void)
{
	static int	i = 0;
	char		*num;
	char		*file;

	num = ft_itoa(i++);
	file = ft_strjoin("src/heredoc/.hd_file_", num);
	free(num);
	return (file);
}

//end[0] instead of 0, to close file descriptor 0
//preventing the program from reading input from the standard input
int	check_fd_heredoc(t_tool *tool, int end[2], t_simple_cmd *cmd)
{
	int	fd_in;

	if (tool->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}
