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


static char	*here_doc_content(char *delim, char quote)
{
	char	*content;
	char	*line;

	content = ft_strdup("");
	line = readline("> ");
	while (line != NULL && (ft_strequ(line, delim) != 0))
	{
		content = join_line(content, line, quote);
		if (content == NULL)
			break ;
		line = readline("here_doc: ");
	}
	check_line_and_free(line, delim);
	return (content);
}

static void	heredoc_proc(int pipe_fd[2], char *delim, char quote)
{
	char	*content;

	sig_handl();
	content = here_doc_content(delim, quote);
	if (content == NULL)
		exit(EXIT_FAILURE);
	ft_putstr_fd(content, pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	free(content);
	exit(EXIT_SUCCESS);
}

static char	*get_content_from_pipe(int pipe_fd[2])
{
	int		res;
	char	*line;
	char	*content;

	content = ft_strdup("");
	res = get_next_line(pipe_fd[0], &line);
	while (res != END_OF_FILE)
	{
		if (res == GNL_ERROR)
		{
			free(content);
			return (NULL);
		}
		content = join_line(content, line, SINGLE_QUOTE);
		res = get_next_line(pipe_fd[0], &line);
		if (content == NULL)
			return (NULL);
	}
	if (line != NULL)
		free(line);
	return (content);
}

static char	*handle_child_process_quit(int pid, int pipe_fd[2])
{
	int		status;
	char	*content;

	sig_handl();
	content = NULL;
	close(pipe_fd[1]);
	if ((waitpid(pid, &status, 0) == -1))
		perror("heredoc: ");
	if (WIFEXITED(status))
	{
		g_last_ret_code = WEXITSTATUS(status);
		if (g_last_ret_code == 0)
		{
			content = get_content_from_pipe(pipe_fd);
			if (content == NULL)
				ft_err(NULL, NULL);
		}
		else
			g_last_ret_code = 130;
	}
	close(pipe_fd[0]);
	return (content);
}

void	*heredoc(t_lexer *lexi)
{
	int		pid;
	int		fd[2];
	char	*delim;
	char	quote;
	char	*line;

	line = NULL;
	quote = '"';
	while (lexi != NULL)
	{
		if (lexi->token == LESS_LESS)
		{
			delim = ft_strdup(lexi->next->str);
			if ((pipe(fd) == -1))
				return (ft_err("pipe failed", strerror(errno)), NULL);
			pid = fork();
			if (pid == -1)
				ft_err("fork failed", strerror(errno));
			else if (pid == 0)
				heredoc_proc(fd, delim, quote);
			else
				line = handle_child_process_quit(pid, fd);
			lexi->str = line;
		}
		lexi = lexi->next;
	}
}
