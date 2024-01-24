/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:50:03 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:36:21 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_data(t_tool *data, bool has_history)
{
	if (data && data->arg)
		ft_free(data->arg);
	if (data && data->lexer)
		lst_clear(&data->lexer);
	if (data && data->env)
		del_env(data->env);
	if (data && data->pipes)
		free_pipe(data->pipes);
	if (data && data->envp)
		free_arr(data->envp);
	if (has_history == true)
		rl_clear_history();
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

int	sub(char *str, int i, int count, t_lexer **lexer)
{
	char	*tmp;

	tmp = ft_substr(str, i, count);
	new_node(tmp, 0, lexer);
	ft_free(tmp);
	return (count);
}
