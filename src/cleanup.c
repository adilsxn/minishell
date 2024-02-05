/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:50:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/05 14:55:59 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_data(t_tool *data, bool has_history)
{
	printf("OI\n");
	if (data != NULL)
	{
		printf("Oi1\n");
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

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
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

char	*freer(t_envy **ex, char *str, char **str1)
{
	char	*ret;

	free_array(str1);
	if ((*ex)->str2 != NULL)
		ret = ft_strdup((*ex)->str2);
	else
		ret = NULL;
	ft_free2((void **)&(*ex)->str2);
	ft_free2((void**)&(*ex));
	ft_free(str);
	return (ret);
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
