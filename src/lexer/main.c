/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/10/09 19:41:03 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(void)
{
	t_lexer	*lexer_list = NULL;
	char 	str[] = "cat > 'a'";
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
	t_tool *tool = malloc(sizeof(t_tool));
	printf("0\n");
	tool->lexer = lexer_list;
	// while (tool->lexer->next)
	// {
	// 	if (tool->lexer->str)
	// 		printf("%s\n", tool->lexer->str);
	// 	if (tool->lexer->token != 0)
	// 		printf("%i\n", tool->lexer->token);
	// 	tool->lexer = tool->lexer->next;
	// }
	//printf("%s\n", tool->lexer->str);
	printf("2\n");
	parser(tool);
	printf("3\n");
	// while (tool->simple_cmd->next)
	// {
	// 	if (tool->lexer->str)
	// 		printf("%s\n", tool->simple_cmd->str);
	// 	tool->simple_cmd = tool->simple_cmd->next;
	// }
	// printf("%s\n", tool->simple_cmd->str);
	return (0);
}
