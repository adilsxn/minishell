/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/09/11 13:58:39 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	t_lexer	*lexer_list = NULL;

	if (argc != 1 || argv[1])
	{
		printf("This program does not accept arguments.\n");
		return (1);
	}
	len_word(0, "cat 'a' > file", &lexer_list);
	len_word(4, "cat 'a' > file", &lexer_list);
	len_word(10, "cat 'a' > file", &lexer_list);
	while (lexer_list->next)
	{
		printf("%s\n", lexer_list->str);
		lexer_list = lexer_list->next;
	}
	printf("%s\n", lexer_list->str);
	return (0);
}
