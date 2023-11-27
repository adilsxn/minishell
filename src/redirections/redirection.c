/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:49:13 by matilde           #+#    #+#             */
/*   Updated: 2023/11/27 20:28:56 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	append_outfile(t_lexer *redirect)
{
	int	fd;

	if (redirect->token == GREAT_GREAT)
		fd = open(redirect->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirect->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		ft_putstr_fd("minishell: dup2 error\n", 2);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

//if dup fails return, if it goes well, great
//subsequent writes to standard output will be directed to that file
int	handle_outfile(t_lexer *redirect)
{
	int	fd;

	fd = append_outfile(redirect);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 1) < 0)
	{
		ft_putstr_fd("minishell: dup2 error\n", 2);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	check_redirect(t_simple_cmd *cmd)
{
	t_lexer	*start;

	start = cmd->redirect;
	while (cmd->redirect)
	{
		if (cmd->redirect->token == LESS)
		{
			if (handle_infile(cmd->redirect->str) == 1)
				return (1);
		}
		else if (cmd->redirect->token == GREAT \
			|| cmd->redirect->token == GREAT_GREAT)
		{
			if (handle_outfile(cmd->redirect) == 1)
				return (1);
		}
		else if (cmd->redirect->token == LESS_LESS)
		{
			if (handle_infile(cmd->hd_file) == 1)
				return (1);
		}
		cmd->redirect = cmd->redirect->next;
	}
	cmd->redirect = start;
	return (0);
}
