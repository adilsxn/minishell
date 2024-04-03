/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:14:49 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/10 16:14:49 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_input(t_rdr *rdr)
{
	int	fmode;
    char *tmp;

	rdr->fd = -1;
	rdr->type = LESS;
	fmode = O_RDONLY;
    tmp = ft_strchr(rdr->value2, '$');
    tmp++;
	if (!(rdr->value) && tmp)
		return (ft_err(tmp, "Ambiguous redirect", NULL, 1), -1);
	if (ft_strequ("\"\"", rdr->value) == 1)
		return (ft_err("", "No such file or directory", NULL, 1), -1);
	rdr->fd = open(rdr->value, fmode, 0044);
	if (rdr->fd == -1)
		return (ft_err(rdr->value, NULL, strerror(errno), 1), -1);
	return (0);
}

int	handle_output(t_rdr *rdr)
{
	int	fmode;
    char *tmp;

	rdr->fd = -1;
	rdr->type = GREAT;
	fmode = O_WRONLY | O_CREAT | O_TRUNC;
    tmp = ft_strchr(rdr->value2, '$');
    tmp++;
	if (!(rdr->value) && tmp)
		return (ft_err(tmp, "Ambiguous redirect", NULL, 1), -1);
	if (ft_strequ("\"\"", rdr->value) == 1)
		return (ft_err("", "No such file or directory", NULL, 1), -1);
	rdr->fd = open(rdr->value, fmode, 0644);
	if (rdr->fd == -1)
		return (ft_err(rdr->value, NULL, strerror(errno), 1), -1);
	return (0);
}

int	handle_heredoc(t_rdr *rdr)
{
	int	fmode;

	rdr->fd = -1;
	rdr->type = LESS_LESS;
	fmode = O_RDONLY;
	rdr->fd = open(rdr->value, fmode, 0044);
	if (rdr->fd == -1)
		return (ft_err(rdr->value, NULL, strerror(errno), 1), -1);
	return (0);
}

int	handle_append(t_rdr *rdr)
{
	int	fmode;
    char *tmp;

	rdr->fd = -1;
	rdr->type = GREAT_GREAT;
	fmode = O_WRONLY | O_CREAT | O_APPEND; 
    tmp = ft_strchr(rdr->value2, '$');
    tmp++;
	if (!(rdr->value) && tmp)
		return (ft_err(tmp, "Ambiguous redirect", NULL, 1), -1);
	if (ft_strequ("\"\"", rdr->value) == 1)
		return (ft_err("", "No such file or directory", NULL, 1), -1);
	rdr->fd = open(rdr->value, fmode, 0644);
	if (rdr->fd == -1)
		return (ft_err(rdr->value, NULL, strerror(errno), 1), -1);
	return (0);
}
