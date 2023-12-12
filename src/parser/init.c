/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:32:32 by matilde           #+#    #+#             */
/*   Updated: 2023/11/26 18:55:39 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser_tool	init_parser_tool(t_lexer *lexer_list, t_tool *tool)
{
	t_parser_tool	parser_tool;

	parser_tool.lexer = lexer_list;
	parser_tool.redirect = NULL;
	parser_tool.nb_redirect = 0;
	parser_tool.tool = tool;
	return (parser_tool);
}

void	init_tool(t_tool *tool)
{
	tool->simple_cmd = NULL;
	tool->our_env = NULL;
	tool->lexer = NULL;
	tool->reset = false;
	tool->heredoc = false;
}

void	reset_tool(t_tool *tool)
{
	cmd_clear(&tool->simple_cmd);
	free(tool->arg);
	init_tool(tool);
	tool->reset = true;
	minishell_loop(tool);
}
