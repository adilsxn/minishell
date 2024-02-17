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
	signal_handler(SIG_IGN, SIGQUIT);
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

void handle_hdoc_child(pid_t pid, int status, t_rdr *rdr, t_lexer *lexi)
{
    signal_handler(sig_hdoc_parent, SIGINT);
	if (waitpid(pid, &status, 0) == -1)
			ft_err("waitpid failed", strerror(errno), NULL, 1);
    get_exit_code(status);
    rdr->fd = open(rdr->value, O_RDONLY, 0044);
    if (rdr->fd == -1)
        ft_err("heredoc failed", lexi->str, strerror(errno), 1);
}

int	handle_heredoc(t_lexer *lexer, t_env *env, t_rdr *rdr)
{
	char	*delim;
	pid_t	pid;
	int		status;

    status = 0;
	rdr->type = LESS_LESS;
	delim = lexer->str;
	rdr->fd = -1;
	name_heredoc_file(rdr);
	unlink(rdr->value);
	rdr->fd = open(rdr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (rdr->fd == -1)
		return (ft_err("heredoc failed", lexer->str, strerror(errno), 1), 1);
	pid = fork();
	if (pid == 0)
		get_line_hdoc(delim, env, rdr->fd);
	else
        handle_hdoc_child(pid, status, rdr, lexer);
	return (status);
}
