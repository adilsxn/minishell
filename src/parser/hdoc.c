/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:34:39 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/12 10:59:30 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	expand_heredoc(t_env *env, int fd, char *content, char **delim)
{
	bool	has_quotes;

	has_quotes = delim_has_quotes(*delim);
	if (has_quotes == true)
	{
		if (*delim[0] == '\'')
			del_quote(*delim, '\'');
		del_quote(*delim, '\"');
	}
	if (!content)
		return (ft_err(HD_W, *delim, NULL, 1), true);
	if (ft_strequ(*delim, content) == 1)
		return (true);
	if (has_quotes == false)
		content = expander(env, content);
	ft_putendl_fd(content, fd);
	ft_free((void **)&content);
	return (false);
}

static bool	get_line_hdoc(char *delim, t_env *env, int fd)
{
	char	*input;

	signal_handler(sig_hdoc_child, SIGINT);
	while (true)
	{
		input = readline("heredoc> ");
		if (expand_heredoc(env, fd, input, &delim))
			break ;
	}
	ft_free((void **)&input);
	close(fd);
	exit(EXIT_SUCCESS);
}

static void	handle_hdoc_child(pid_t pid, int status, char *delim)
{
	signal_handler(sig_hdoc_parent, SIGINT);
	ft_free((void **)&delim);
	if (waitpid(pid, &status, 0) == -1)
		ft_err("waitpid failed", strerror(errno), NULL, 1);
	get_exit_code(status);
}

void	parse_heredoc(t_lexer *lexer, t_env *env)
{
	char	*delim;
	int		fd;
	pid_t	pid;
	int		status;
	t_lexer	*it;

	status = 0;
	fd = -1;
	it = lexer;
	while (it != NULL)
	{
		if (it->token == LESS_LESS)
		{
			delim = ft_strdup(it->str);
			name_heredoc_file(it);
			fd = open(it->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				ft_err("heredoc failed", "", strerror(errno), 1);
			pid = fork();
			if (pid == 0)
				get_line_hdoc(delim, env, fd);
			handle_hdoc_child(pid, status, delim);
		}
		it = it->next;
	}
}
