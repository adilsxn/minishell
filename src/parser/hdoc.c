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
#include <fcntl.h>

/* Process terminating with default action of signal 11 (SIGSEGV)
==29867==  General Protection Fault
==29867==    at 0x10E881: ft_strequ (ft_strequ.c:19)
==29867==    by 0x10A4A1: handle_heredoc (hdoc.c:70)
==29867==    by 0x10A54E: get_line_hdoc (hdoc.c:89)
==29867==    by 0x10A61B: heredoc (hdoc.c:115)
==29867==    by 0x10D157: minishell_loop (main.c:49)
==29867==    by 0x10D28B: main (main.c:75)
 */
static bool	name_heredoc_file(t_rdr *rdr)
{
	static int	i;
	char		*number;
	t_rdr		*it;

	if (i == 0)
		i = 0;
	it = rdr;
	number = ft_itoa(i);
	if (!number)
		return (ft_err("heredoc failed", NULL, NULL, 1), false);
	it->value = ft_strjoin(HD_FILE, number);
	i++;
	ft_free((void **)&number);
	return (true);
}

static bool	delim_has_quotes(char *str)
{
	int	i;
	int	nbr_quotes;

	i = 0;
	nbr_quotes = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			nbr_quotes++;
		i++;
	}
	if (nbr_quotes >= 2)
		return (true);
	return (false);
}

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

	g_last_ret_code = 0;
	while (true && g_last_ret_code == 0)
	{
		signal_handler();
		input = readline("heredoc> ");
		if (expand_heredoc(env, fd, input, &delim))
			break ;
	}
	ft_free((void **)&input);
	close(fd);
	return (true);
}

//TODO: If delim has quotes no expansion, else expand
int	handle_heredoc(t_lexer *lexer, t_env *env, t_rdr *rdr)
{
	char	*delim;

	rdr->type = LESS_LESS;
	delim = lexer->str;
	rdr->fd = -1;
	name_heredoc_file(rdr);
	unlink(rdr->value);
	rdr->fd = open(rdr->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (rdr->fd == -1)
		return (ft_err("heredoc failed", lexer->str, strerror(errno), 1), 1);
	get_line_hdoc(delim, env, rdr->fd);
	// ft_free((void **)&it->str);
	rdr->fd = open(rdr->value, O_RDONLY, 0044);
	if (rdr->fd == -1)
		return (ft_err("heredoc failed", lexer->str, strerror(errno), 1), 1);
	return (0);
}
