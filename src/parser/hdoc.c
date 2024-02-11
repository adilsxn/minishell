/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:34:39 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/03 19:36:56 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/* Process terminating with default action of signal 11 (SIGSEGV)
==29867==  General Protection Fault
==29867==    at 0x10E881: ft_strequ (ft_strequ.c:19)
==29867==    by 0x10A4A1: handle_heredoc (hdoc.c:70)
==29867==    by 0x10A54E: get_line_hdoc (hdoc.c:89)
==29867==    by 0x10A61B: heredoc (hdoc.c:115)
==29867==    by 0x10D157: minishell_loop (main.c:49)
==29867==    by 0x10D28B: main (main.c:75)
 */
static bool name_heredoc_file(t_rdr *rdr)
{
    int i;
    char *number;
    t_rdr *it;

    i = 0;
    it = rdr;
    number = NULL;
    while (it != NULL)
    {
        number = ft_itoa(i);
        if (!number)
            return (ft_err("heredoc failed", NULL, NULL, 1), false);
        if (it->type == LESS_LESS)
        {
            it->value = ft_strjoin(HD_FILE, number);
            i++;
        }
        it = it->next;
        ft_free(number);
    }
    return (true);
}

static bool delim_has_quotes(char *str)
{
    int i;
    int nbr_quotes;

    i = -1;
    nbr_quotes = 0;
    while(str[++i] != '\0')
    {
        if ( str[i] == '\'' || str[i] == '\"')
            nbr_quotes++;
    }
    if (nbr_quotes >= 2)
        return (true);
    return(false);
}

static bool expand_heredoc(t_env *env, int fd, char *content, char **delim)
{
    bool has_quotes;

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
    if(has_quotes == false) 
        content = expander(env, content);
    ft_putendl_fd(content, fd);
    ft_free(content);
    return (false);
}

static bool	get_line_hdoc(char *delim, t_env *env, int fd)
{
	char	*input;

	while (true)
	{
        signal_handler();
        input = readline("heredoc> ");
        if (expand_heredoc(env, fd, input, &delim))
            break ;
	}
    ft_free(input);
    close(fd);
    return (true);
}

//TODO: If delim has quotes no expansion, else expand
int	handle_heredoc(t_lexer *lexer, t_env *env, t_rdr *rdr)
{
    t_lexer *it;
    int fd;
	char	*delim;

    it = lexer;
	while (it != NULL)
	{
		if (it->token == LESS_LESS)
		{
            delim = it->str;
            name_heredoc_file(rdr);
            unlink(it->str);
            fd = open(it->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (ft_err("heredoc failed", it->str, strerror(errno), 1), 1);
            get_line_hdoc(delim, env, fd);
            ft_free(it->str);
		}
		it = it->next;
	}
	return (0);
}
