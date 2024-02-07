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

static int	get_out(int fd, t_rdr *rdr)
{
	int	fmode;

	if (fd >= 0)
		close(fd);
	fmode = O_WRONLY | O_CREAT | O_TRUNC;
	if (rdr->kind == RDR_APP)
		fmode = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(rdr->value, fmode, 0644);
	if (fd == -1)
		return (ERROR);
	if (rdr->kind == RDR_OUT)
		ft_putstr_fd("", fd);
	return (fd);
}

static int	set_fd_out(t_rdr *rdr)
{
	int	fd;
	int	dup_fd;

	fd = -1;
	while (rdr != NULL)
	{
		if (rdr->kind == RDR_OUT || rdr->kind == RDR_APP)
		{
			fd = get_out(fd, rdr);
            if (fd == ERROR)
                return (ERROR);
			dup_fd = dup2(fd, STDOUT_FILENO);
			close(fd);
			if (dup_fd == -1)
				return (ERROR);
		}
		rdr = rdr->next;
	}
	if (fd != -1 || fd != ERROR)
		close(fd);
	return (fd);
}

static int	get_in(int fd, t_rdr *rdr)
{
	if (fd >= 0)
		close(fd);
	if (rdr->kind == RDR_HD || rdr->kind == RDR_IN)
		fd = open(rdr->value, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	return (fd);
}

static int	set_fd_in(t_rdr *rdr)
{
	int	fd;
	int	dup_fd;

	fd = -1;
	while (rdr != NULL)
	{
		if (rdr->kind == RDR_IN || rdr->kind == RDR_HD)
		{
			fd = get_in(fd, rdr);
			if (fd == ERROR)
				return (ERROR);
			dup_fd = dup2(fd, STDIN_FILENO);
			close(fd);
			if (dup_fd == -1)
				return (ERROR);
		}
		rdr = rdr->next;
	}
	if (fd != -1)
		close(fd);
	return (fd);
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
