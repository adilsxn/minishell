/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:49:18 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 21:11:51 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	set_fd_out(t_rdr *rdr)
{
	int	dup_fd;

	while (rdr != NULL)
	{
		if (rdr->type == GREAT || rdr->type == GREAT_GREAT)
		{
			dup_fd = dup2(rdr->fd, STDOUT_FILENO);
			ft_close(rdr->fd);
			if (dup_fd == -1)
				return (ERROR);
		}
		rdr = rdr->next;
	}
	return (0);
}

static int	set_fd_in(t_rdr *rdr)
{
	int	dup_fd;

	while (rdr != NULL)
	{
		if (rdr->type == LESS || rdr->type == LESS_LESS)
		{
			dup_fd = dup2(rdr->fd, STDIN_FILENO);
			ft_close(rdr->fd);
			if (dup_fd == -1)
				return (ERROR);
		}
		rdr = rdr->next;
	}
	return (0);
}

int	exec_rdr(t_rdr *rdr)
{
	int	fd_out;
	int	fd_in;

	fd_out = set_fd_out(rdr);
	fd_in = set_fd_in(rdr);
	if (fd_out == ERROR || fd_in == ERROR)
		return (-1);
	return (0);
}
