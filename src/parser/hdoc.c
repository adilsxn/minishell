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
#include <stdbool.h>
/* Process terminating with default action of signal 11 (SIGSEGV)
==29867==  General Protection Fault
==29867==    at 0x10E881: ft_strequ (ft_strequ.c:19)
==29867==    by 0x10A4A1: handle_heredoc (hdoc.c:70)
==29867==    by 0x10A54E: get_line_hdoc (hdoc.c:89)
==29867==    by 0x10A61B: heredoc (hdoc.c:115)
==29867==    by 0x10D157: minishell_loop (main.c:49)
==29867==    by 0x10D28B: main (main.c:75)
 */
static bool name_heredoc_file(t_lexer *lexi)
{
    int i;
    char *number;
    t_lexer *it;

    i = 0;
    it = lexi;
    while (it != NULL)
    {
        number = ft_itoa(i);
        if (!number)
            return (ft_err("heredoc failed", ""), false);
        if (it->token == LESS_LESS)
        {
            it->str = ft_strjoin(HD_FILE, number);
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
static bool handle_heredoc(t_tool *data, int fd, char *content, char **delim)
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
        return (ft_err(HD_W, *delim), true);
    if (ft_strequ(*delim, content) == 1)
        return (true);
    if(has_quotes == false) 
        content = expander(data->env, content);
    ft_putendl_fd(content, fd);
    ft_free(content);
    return (false);
}

static bool	get_line_hdoc(char *delim, t_tool *data, int fd)
{
	char	*input;

	while (true)
	{
        signal_handler();
        input = readline("heredoc> ");
        signal_handler_idle();
        if (handle_heredoc(data, fd, input, &delim))
            break ;
	}
    ft_free(input);
    //TODO: Expand the content before writing to file
    return (true);
}

//TODO: If delim has quotes no expansion, else expand
int	heredoc(t_tool *data)
{
    t_lexer *it;
    int fd;
	char	*delim;

    it = data->lexer;
    name_heredoc_file(it);
	while (it != NULL)
	{
		if (it->token == LESS_LESS)
		{
            delim = it->next->str;
            unlink(it->str);
            fd = open(it->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return (ft_err("heredoc failed", NULL), 1);
            get_line_hdoc(delim, data, fd);
            if (fd != -1)
                close(fd);
		}
		it = it->next;
	}
	return (0);
}
