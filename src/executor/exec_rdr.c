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

/* static int	get_out(int fd, t_rdr *rdr)
{
	int	fmode;

	if (fd >= 0)
		ft_close(fd);
	fmode = O_WRONLY | O_CREAT | O_TRUNC;
	if (rdr->type == RDR_APP)
		fmode = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(rdr->value, fmode, 0644);
	if (fd == -1)
		return (ft_err(rdr->value, NULL, NULL, 1), ERROR);
	if (rdr->type == RDR_OUT)
		ft_putstr_fd("", fd);
	return (fd);
} */

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

/* static int	get_in(int fd, t_rdr *rdr)
{
	if (fd >= 0)
		ft_close(fd);
	if (rdr->type == RDR_HD || rdr->type == RDR_IN)
		fd = open(rdr->value, O_RDONLY);
	if (fd == -1)
		return (ft_err(rdr->value, NULL, NULL, 1), ERROR);
	return (fd);
} */

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
