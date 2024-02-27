/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:12:28 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/02/03 19:36:56 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_error(char *cmd, char *cmd_path)
{
	struct stat	var;

	stat(cmd, &var);
	if (!ft_strchr(cmd, '/') && !cmd_path)
		return (ft_err(cmd, "command not found", NULL, 127), 127);
	if (access(cmd, F_OK) != 0)
		return (ft_err(cmd, "", strerror(errno), 127), 127);
	else if (S_ISDIR(var.st_mode))
		return (ft_err(cmd, "", "Is a directory", 126), 126);
	else if (access(cmd, F_OK | X_OK) != 0)
		return (ft_err(cmd, "", strerror(errno), 126), 126);
	return (EXIT_SUCCESS);
}

static void	child_proc(t_cmd *cmd)
{
	signal_handler(sig_new_prompt, SIGINT);
	if (cmd->rdir != NULL && (exec_rdr(cmd->rdir) == -1))
	{
		perror("minishell");
		exit(1);
	}
	if (cmd->path == NULL)
		exit(0);
	clean_fds();
	if (execve(cmd->path, cmd->args, NULL) == ERROR)
		ft_err("execve failed", strerror(errno), NULL, 1);
	exit(1);
}

void	get_exit_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_last_ret_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_last_ret_code = WTERMSIG(wstatus) + 128;
}

void	exec_bin(t_cmd *cmd)
{
	int	pid;
	int	status;

	if (cmd->path == NULL)
	{
		g_last_ret_code = cmd_error(cmd->args[0], cmd->path);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_err("fork failed", strerror(errno), NULL, 1);
		g_last_ret_code = 1;
	}
	else if (pid == 0)
		child_proc(cmd);
	else
	{
		signal_handler(sig_new_prompt, SIGINT);
		if (waitpid(pid, &status, 0) == -1)
			ft_err("waitpid failed", strerror(errno), NULL, 1);
		get_exit_code(status);
	}
}
