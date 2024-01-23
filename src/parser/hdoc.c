/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:34:39 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/23 13:55:32 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <string.h>


static char	*get_line_hdoc(char *delim)
{
	char	*content;
	char	*line;

	content = ft_strdup("");
	line = readline("> ");
	while (line != NULL && (ft_strequ(line, delim) != 0))
	{
		content = ft_strjoin(content, line);
		if (content == NULL)
			break ;
		line = readline("> ");
	}
    if (!line)
        ft_free(line);
	else
		ft_err(HD_W, delim);
	return (content);
}

static void	heredoc_proc(int pipe_fd[2], char *delim)
{
	char	*line;

	sig_handl();
	line = get_line_hdoc(delim);
	if (line == NULL)
		exit(EXIT_FAILURE);
	ft_putstr_fd(line, pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_free(line);
	exit(EXIT_SUCCESS);
}

static char	*get_line_pipe(int pipe_fd[2])
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	line = get_next_line(pipe_fd[0]);
	while (line != NULL)
	{
		content = ft_strjoin(content, line);
		line = get_next_line(pipe_fd[0]);
		if (content == NULL)
			return (NULL);
	}
    ft_free(line);
	return (content);
}

static char	*handle_child_exit(int pid, int pipe_fd[2])
{
	int		status;
	char	*content;

	sig_handl();
	content = NULL;
	close(pipe_fd[1]);
	if ((waitpid(pid, &status, 0) == -1))
        ft_err("heredoc", strerror(errno));
	if (WIFEXITED(status))
	{
		g_last_ret_code = WEXITSTATUS(status);
		if (g_last_ret_code == 0)
		{
			content = get_line_pipe(pipe_fd);
			if (content == NULL)
				ft_err(NULL, NULL);
		}
		else
			g_last_ret_code = 130;
	}
	close(pipe_fd[0]);
	return (content);
}

int heredoc(t_lexer *lexi)
{
	int		pid;
	int		fd[2];
	char	*delim;
	char	*line;

	line = NULL;
	while (lexi != NULL)
	{
		if (lexi->token == LESS_LESS)
		{
			delim = lexi->next->str;
			if ((pipe(fd) == -1))
				return (ft_err("pipe failed", strerror(errno)),1);
			pid = fork();
			if (pid == -1)
				return(ft_err("fork failed", strerror(errno)), 1);
			else if (pid == 0)
				heredoc_proc(fd, delim);
			else
				line = handle_child_exit(pid, fd);
			lexi->str = line;
		}
		lexi = lexi->next;
	}
    return (0);
}
