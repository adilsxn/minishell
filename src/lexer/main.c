/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/10/12 12:37:28 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	t_lexer	*lexer_list = NULL;
	char 	str[] = "cat a < file -e";
	int 	count;

	count = -1;
	while (++count < 19)
		count += len_word(count, str, &lexer_list);
	t_tool tool;
	init_tool(&tool);
	tool.lexer = lexer_list;
	parser(&tool);
	int i = 0;
	t_tool tool2 = tool;
	while (tool.simple_cmd->str[i])
	{
		if (tool.simple_cmd->str[i])
			printf("%i, %s\n", i, tool.simple_cmd->str[i]);
		i++;
	}
	while (tool.simple_cmd->redirect)
	{
		if (tool.simple_cmd->redirect->token)
			printf("token %i\n", tool.simple_cmd->redirect->token);
		if (tool.simple_cmd->redirect->str)
			printf("%s\n", tool.simple_cmd->redirect->str);
		break ;
	}
	tool = tool2;
	cmd_clear(&tool.simple_cmd);
	return (0);
}
