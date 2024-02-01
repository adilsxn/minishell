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
//TODO: make get_in get the unique name for the hd_file
static int	get_out(int fd, t_rdr *rdr)
{
	int	fmode;
	int	fperm;

	if (fd >= 0)
		close(fd);
	fmode = O_WRONLY | O_CREAT | O_TRUNC;
	if (rdr->kind == RDR_APP)
		fmode = O_WRONLY | O_CREAT | O_APPEND;
	fperm = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	fd = open(rdr->value, fmode, fperm);
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
			dup_fd = dup2(fd, STDOUT_FILENO);
			close(fd);
			if (dup_fd == -1)
				return (ERROR);
		}
		rdr = rdr->next;
	}
	close(fd);
	return (fd);
}

static int	get_in(int fd, t_rdr *rdr)
{
	int	heredoc_perm;

	if (fd >= 0)
		close(fd);
	heredoc_perm = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
	if (rdr->kind == RDR_HD)
		fd = open(HD_FILE, O_RDWR | O_CREAT | O_TRUNC, heredoc_perm);
	else
		fd = open(rdr->value, O_RDONLY, 0);
	if (fd == -1)
		return (ERROR);
	if (rdr->kind == RDR_HD)
	{
		ft_putstr_fd(rdr->value, fd);
		close(fd);
		fd = open(HD_FILE, O_RDONLY, 0);
		if (fd == -1)
			return (ERROR);
	}
	return (fd);
}

static int	set_fd_in(t_rdr *rdr)
{
	int	fd;
	int	dup_fd;

	fd = -1;
	while (rdr != NULL )
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
	close(fd);
	unlink(HD_FILE);
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
