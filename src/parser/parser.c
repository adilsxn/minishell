/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:48:03 by matilde           #+#    #+#             */
/*   Updated: 2023/12/04 13:57:56 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//first rm redirection from lexer, and put it in parser_tools
//args: words and tokens input
//put str(with args) in new cmd (simple command struct) and remove from lexer
//simple cmd struct has all args all cmds without redirections in str and
//redirections in other parameter
t_simple_cmd	*init_cmd(t_parser_tool *parser_tool)
{
	char	**str;
	int		i;
	int		args;
	t_lexer	*tmp;

	i = 0;
	rm_redirect(parser_tool);
	args = count_arg(parser_tool->lexer);
	str = ft_calloc(args + 1, sizeof(char *));
	if (!str)
		ft_error(1, parser_tool->tool);
	tmp = parser_tool->lexer;
	while (args > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			del_one(&parser_tool->lexer, tmp->i);
			tmp = parser_tool->lexer;
		}
		args--;
	}
	return (cmd_new(str, parser_tool->nb_redirect, parser_tool->redirect));
}

//check for double pipes : error 
//transfer from lexerlist to simple cmd before and after pipe
//assign the node as the first command in the tool->simple_cmd list.
//If tool->simple_cmd is not NULL, adds the node to the end of the list
//update tool->lexer with parser_tool->lexer, since tokens are removed
int	parser(t_tool *tool)
{
	t_simple_cmd	*node;
	t_parser_tool	parser_tool;

	tool->simple_cmd = NULL;
	count_pipes(tool->lexer, tool);
	if (tool->lexer->token == PIPE)
		return (double_token_error(tool));
	while (tool->lexer)
	{
		if (tool->lexer && tool->lexer->token == PIPE)
			del_one(&tool->lexer, tool->lexer->i);
		if (pipe_error(tool) == 1)
			return (1);
		parser_tool = init_parser_tool(tool->lexer, tool);
		node = init_cmd(&parser_tool);
		if (!node)
			ft_error(0, tool);
		if (!tool->simple_cmd)
			tool->simple_cmd = node;
		else
			add_cmd(&tool->simple_cmd, node);
		tool->lexer = parser_tool.lexer;
	}
	return (0);
}
