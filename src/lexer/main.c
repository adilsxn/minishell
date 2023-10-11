/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/10/11 16:45:57 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	t_lexer	*lexer_list = NULL;
	char 	str[] = "cat | 'a'";
	int 	count;

	count = -1;
	while (++count < 19)
		count += len_word(count, str, &lexer_list);
	// while (lexer_list->next)
	// {
	// 	if (lexer_list->str)
	// 		printf("%s\n", lexer_list->str);
	// 	if (lexer_list->token != 0)
	// 		printf("%i\n", lexer_list->token);
	// 	lexer_list = lexer_list->next;
	// }
	// printf("%s\n", lexer_list->str);
	t_tool tool;
	init_tool(&tool);
	tool.lexer = lexer_list;
	// t_lexer	*tmp = tool.lexer;
	// while (tmp)
	// {
	// 	if (tmp->str)
	// 		printf("%s\n", tmp->str);
	// 	if (tmp->token != 0)
	// 		printf("%i\n", tmp->token);
	// 	tmp = tmp->next;
	// }
	printf("what\n");
	parser(&tool);
	printf("yes\n");
	int i = 0;
	t_tool tool2 = tool;
	while (tool.simple_cmd->str[i])
	{
		if (tool.simple_cmd->str[i])
			printf("%s\n", tool.simple_cmd->str[i]);
		i++;
	}
	while (tool.simple_cmd->redirect)
	{
		if (tool.simple_cmd->redirect->str)
			printf("%s\n", tool.simple_cmd->redirect->str);
		if (tool.simple_cmd->redirect->token)
			printf("%i\n", tool.simple_cmd->redirect->token);
		break ;
	}
	tool = tool2;
	cmd_clear(&tool.simple_cmd);
	// free_array(tool.simple_cmd->str);
	// lst_clear(&tool.simple_cmd->redirect);
	// lst_clear(&tool.lexer);
	return (0);
}
