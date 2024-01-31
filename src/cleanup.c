/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:50:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/27 19:22:48 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_data(t_tool *data, bool has_history)
{
	if (data != NULL)
	{
		if (data->arg != NULL)
		 	ft_free(data->arg);
		lst_clear(&data->lexer);
		if (data->pipes)
			free_pipe(data->pipes);
		if (has_history == true)
		{
			rl_clear_history();
			if (data != NULL && data->env)
				del_env(data->env);
		}
	}
}

void	clean_fds(void)
{
	int	fd;

	fd = open(HD_FILE, O_RDONLY | O_CREAT);
	if (fd < 0)
		return ;
	while (fd > STDERR_FILENO)
		close(fd--);
	unlink(HD_FILE);
}

void	freer(t_envy *ex, char *str)
{
	free(ex);
	free(str);
}

void	sub(char *str, int i, int count, t_lexer **lexer, t_tool *tool)
{
	char	*tmp;

	tmp = ft_substr(str, i, count);
	new_node(tmp, 0, lexer, tool);
	ft_free(tmp);
}

bool has_heredoc(t_lexer *lexer)
{
	t_lexer *it;
	it = lexer;

	while (it != NULL)
	{
		if (it->token == LESS_LESS)
			return (true);
		it = it->next;
	}
	return (false);
}
