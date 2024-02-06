/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:23:48 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:23:13 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_bi(t_cmd *cmd, t_tool *data)
{
	int		fd[2];
	t_bi	*builtin;
	int		return_code;

	if (cmd->rdir != NULL)
	{
		fd[STDIN_FILENO] = dup(STDIN_FILENO);
		fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
		exec_rdr(cmd->rdir);
	}
	builtin = get_bi(cmd->args[0]);
	if (builtin == NULL)
	{
		ft_err(cmd->args[0], "could not execute builtin");
		return (2);
	}
	return_code = builtin(cmd->args, data);
	if (cmd->rdir != NULL)
	{
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
	}
	return (return_code);
}
