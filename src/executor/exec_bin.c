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

static void	signal_handler_nonin(void (*handler)(int), int signal)
{
	struct sigaction	event;

	ft_bzero(&event, sizeof(struct sigaction));
	event.sa_handler = handler;
	event.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&event.sa_mask);
	sigaction(signal, &event, NULL);
}

int	cmd_error(t_cmd *cmd, t_tool *data)
{
	struct stat	var;

	if (!cmd->path)
		cmd->path = ft_strdup("");
	stat(cmd->path, &var);
	if (ft_strequ(cmd->args[0], "."))
		return (ft_err(cmd->args[0], NULL, DOT_MSG, 2), 2);
	else if (ft_strequ(cmd->args[0], "..") && !get_env(data->env, "PATH"))
		return (ft_err(cmd->args[0], NULL, "command not found", 126), 126);
	else if (ft_strequ(cmd->args[0], ".."))
		return (ft_err(cmd->args[0], NULL, "command not found", 127), 127);
	else if ((!ft_strchr(cmd->args[0], '/') && cmd->path_on
            && ft_strequ(cmd->path, "")) || ft_strequ(cmd->args[0], ""))
		return (ft_err(cmd->args[0], "command not found", NULL, 127), 127);
	else if (access(cmd->path, F_OK) != 0)
		return (ft_err(cmd->args[0], NULL, strerror(errno), 127), 127);
	else if (S_ISDIR(var.st_mode) || ft_strequ(cmd->args[0], ".."))
		return (ft_err(cmd->args[0], NULL, "Is a directory", 126), 126);
	else if (access(cmd->path, F_OK | X_OK) != 0)
		return (ft_err(cmd->args[0], NULL, strerror(errno), 126), 126);
	return (EXIT_SUCCESS);
}

static void	child_proc(t_cmd *cmd)
{
	signal_handler(sig_new_prompt, SIGINT);
	signal_handler_nonin(sig_new_prompt, SIGQUIT);
	if (cmd->rdir != NULL && (exec_rdr(cmd->rdir) == -1))
	{
		perror("minishell");
		exit(1);
	}
	if (cmd->path == NULL)
		exit(0);
	clean_fds();
	if (execve(cmd->path, cmd->args, NULL) == ERROR)
		ft_err2("execve failed", strerror(errno), NULL);
	exit(1);
}

void	get_exit_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		g_last_ret_code = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		g_last_ret_code = WTERMSIG(wstatus) + 128;
}

void	exec_bin(t_cmd *cmd, t_tool *data)
{
	int	pid;
	int	status;

	g_last_ret_code = cmd_error(cmd, data);
	if (g_last_ret_code > 120 || g_last_ret_code == 2)
		return ;
	pid = fork();
	if (pid == -1)
	{
		ft_err2("fork failed", strerror(errno), NULL);
	}
	else if (pid == 0)
		child_proc(cmd);
	else
	{
		signal_handler_nonin(sig_hdoc_parent, SIGINT);
		signal_handler_nonin(sig_hdoc_parent, SIGQUIT);
		if (waitpid(pid, &status, 0) == -1)
			ft_err2("waitpid failed", strerror(errno), NULL);
		get_exit_code(status);
	}
}
