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

int	msh_void(char **args, t_tool *data)
{
	(void)args;
	(void)data;
	return (EXIT_FAILURE);
}

static t_cmd	*mk_void_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)malloc(sizeof(char *) * 2);
	cmd->args[0] = ft_strdup("void");
	cmd->args[1] = NULL;
	cmd->argc = 1;
	cmd->rdir = NULL;
	cmd->path = ft_strdup("usr/bin/void");
	return (cmd);
}

bool	is_builtin(char *str)
{
	if (ft_strequ(str, "echo"))
		return (true);
	if (ft_strequ(str, "void"))
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

void	free_cmd(t_cmd **cmd)
{
	if ((*cmd) == NULL)
		return ;
	if ((*cmd)->path != NULL)
		ft_free((void **)&(*cmd)->path);
	if ((*cmd)->args != NULL)
		free_arr((*cmd)->args);
	if ((*cmd)->rdir != NULL)
		free_rdr(&((*cmd)->rdir));
	ft_free((void **)&(*cmd));
}

t_cmd	*mk_cmd(t_lexer *lexer, t_env *env)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argc = count_token(lexer);
	cmd->args = build_av(lexer, cmd->argc);
	cmd->rdir = build_rdr(lexer, cmd, env);
	if (cmd->args != NULL && is_builtin(cmd->args[0]) == false)
		cmd->path = cmd_finder(env, cmd->args[0]);
	if (cmd->args == NULL || cmd->argc == 0)
		free_cmd(&cmd);
	if (cmd->io == true && cmd->rdir == NULL)
	{
		free_cmd(&cmd);
		cmd = mk_void_cmd();
		return (cmd);
	}
	return (cmd);
}
