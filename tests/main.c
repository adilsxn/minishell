/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/11/09 18:28:05 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//These environment variables arent considered command-line 
//arguments and are typically provided by the shell 
//or the operating system when the program is executed
int	main(int argc, char **argv, char **env)
{
	t_lexer	*lexer_list = NULL;
	t_tool	tool;
	size_t		count = -1;
	char 	str[] = "FILE='/tmp/1.txt'; echo $FILE";
	char	**exp = NULL;
	int		i = -1;
	char	**tmp;

	if (argc != 1 || argv[1])
	{
		printf("The program does not accept arguments.\n");
		return (1);
	}
	while (++count < ft_strlen(str))
		count += len_word(count, str, &lexer_list);
	init_tool(&tool);
	tool.lexer = lexer_list;
	parser(&tool);
	tool.env = ft_arrdup(env);
	tmp = add_var(tool.env, tool.simple_cmd->str[0]);
	free_array(tool.env);
	tool.env = tmp;
	exp = expander(&tool, tool.simple_cmd->next->str);
	while (exp[++i])
		printf("exp %s\n", exp[i]);
	return (0);
}
