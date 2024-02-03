/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:34:39 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 20:14:57 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
            it->str = ft_strjoin(HD_FILE, number);
        i++;
        it = it->next;
        ft_free(number);
    }
    return (true);
}

static bool handle_heredoc(t_tool *data, int fd, char *content, char *delim)
{
    if (!content)
        return (ft_err(HD_W, delim), true);
    if (ft_strequ(delim, content) == 1)
        return (true);
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
        input = readline("heredoc> ");
        if (handle_heredoc(data, fd, input, delim))
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
            close(fd);
		}
		it = it->next;
	}
	return (0);
}
