/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:12:28 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/23 13:27:20 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static void	child_process(t_cmd *cmd)
{
	sig_handl();
	if (cmd->rdir != NULL
		&& (exec_rdr(cmd->rdir) == -1))
	{
		perror("minishell");
		exit(1);
	}
	if (cmd->path == NULL)
		exit(0);
	clean_fds();
	if (execve(cmd->path, cmd->args, cmd->envp) == ERROR)
		ft_err("execve failed", strerror(errno));
	exit(1);
}

static void	set_ret_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_last_ret_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_last_ret_code  = WTERMSIG(wstatus) + 128;
}

void	exec_bin(t_cmd *cmd)
{
	int		pid;
	int		status;

	if (cmd->path == NULL && cmd->rdir == NULL)
	{
		ft_err(cmd->args[0], "cmd not found");
		g_last_ret_code = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_err( "fork failed", strerror(errno));
		g_last_ret_code = 1;
	}
	else if (pid == 0)
		child_process(cmd);
	else
	{
		sig_handl();
		if (waitpid(pid, &status, 0) == -1)
			ft_err("waitpid failed", strerror(errno));
		set_ret_code(status);
	}
}
