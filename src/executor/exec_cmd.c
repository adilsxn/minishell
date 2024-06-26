/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_s_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:16:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:22:21 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_cmd(t_tool *data)
{
	t_cmd	*cmd;

	cmd = mk_cmd(data->lexer, data->env);
	if (cmd == NULL)
		return ;
	if ((is_builtin(cmd->args[0]) != 0))
		g_last_ret_code = exec_bi(cmd, data);
	else
		exec_bin(cmd, data);
	free_cmd(&cmd);
}
