/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:10:04 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 13:10:04 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(char *str)
{
    if (ft_strequ(str, "echo"))
        return (true);
    if (ft_strequ(str, "cd"))
        return (true);
    if (ft_strequ(str, "pwd"))
        return (true);
    if (ft_strequ(str, "export"))
        return (true);
    if (ft_strequ(str, "unset"))
        return (true);
    if (ft_strequ(str, "env"))
        return (true);
    if (ft_strequ(str, "exit"))
        return (true);
    return (false);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->path != NULL)
		ft_free(cmd->path);
	if (cmd->args != NULL)
		ft_free(cmd->args);
	if (cmd->envp != NULL)
		free_arr(cmd->envp);
	if (cmd->rdir != NULL)
		free_rdr(cmd->rdir);
	ft_free(cmd);
}

t_cmd *mk_cmd(t_tool *data)
{
	t_cmd *cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->envp = ft_arrdup(data->envp);
	cmd->args = build_av(data->lexer);
	cmd->rdir = build_rdr(data->lexer);
	cmd->argc = count_token(data->lexer);
	if (cmd->args != NULL  && is_builtin(cmd->args[0]) == true)
	    cmd->path = cmd_finder(data, cmd->args[0]);
	if (cmd->args == NULL || cmd->envp == NULL ||
	    cmd->rdir == NULL || cmd->envp == NULL)
	{
		free_cmd(cmd);
		cmd = NULL;
	}
	return (cmd);
}
