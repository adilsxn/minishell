/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matde-je <matde-je@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:30:06 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/24 18:22:53 by matde-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_bin_pipe(t_cmd *cmd)
{
	if (cmd->path == NULL && cmd->rdir == NULL)
	{
		ft_err(cmd->args[0], "cmd not found");
		return (127);
	}
	if (cmd->rdir != NULL && (exec_rdr(cmd->rdir) == -1))
	{
		ft_err("redirection failed", NULL);
		return (1);
	}
	if (cmd->path == NULL)
		return (0);
	if (execve(cmd->path, cmd->args, cmd->envp) == ERROR)
		ft_err("execve failed", strerror(errno));
	return (errno);
}

static void	exec_pipe_child(t_ppe *proc, int proc_fd[2], t_tool *data)
{
	sig_handl();
	close(proc_fd[STDIN_FILENO]);
	clean_fds();
	if ((is_builtin(proc->cmd->args[0]) != 0))
		proc->exit_code = exec_bi(proc->cmd, data);
	else
		proc->exit_code = exec_bin_pipe(proc->cmd);
	exit(proc->exit_code);
}

static void	create_proc(t_ppe *proc, int proc_fd[2], int std_fd[2],
		t_tool *data)
{
	int	pipe_fd[2];

	dup2(proc_fd[STDIN_FILENO], STDIN_FILENO);
	close(proc_fd[STDIN_FILENO]);
	if (proc->next != NULL)
	{
		pipe(pipe_fd);
		proc_fd[STDIN_FILENO] = pipe_fd[0];
		proc_fd[STDOUT_FILENO] = pipe_fd[1];
	}
	else
		proc_fd[STDOUT_FILENO] = dup(std_fd[STDOUT_FILENO]);
	dup2(proc_fd[STDOUT_FILENO], STDOUT_FILENO);
	close(proc_fd[STDOUT_FILENO]);
	proc->pid = fork();
	if (proc->pid == 0)
	{
		close(std_fd[STDIN_FILENO]);
		close(std_fd[STDOUT_FILENO]);
		exec_pipe_child(proc, proc_fd, data);
	}
}

static void	wait_procs(t_ppe *procs)
{
	while (procs != NULL)
	{
		waitpid(procs->pid, &procs->exit_code, 0);
		if (WIFEXITED(procs->exit_code))
			procs->exit_code = WEXITSTATUS(procs->exit_code);
		else if (WIFSIGNALED(procs->exit_code))
			procs->exit_code = WTERMSIG(procs->exit_code) + 128;
		if (procs->next == NULL)
			g_last_ret_code = procs->exit_code;
		procs = procs->next;
	}
}

void	exec_pipe(t_tool *data)
{
	int		std_fd[2];
	int		proc_fd[2];
	t_ppe	*proc;

	sig_handl();
	std_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fd[STDOUT_FILENO] = dup(STDOUT_FILENO);
	proc_fd[STDIN_FILENO] = dup(STDIN_FILENO);
	proc_fd[STDOUT_FILENO] = -1;
	proc = data->pipes;
	while (proc != NULL)
	{
		create_proc(proc, proc_fd, std_fd, data);
		proc = proc->next;
	}
	dup2(std_fd[STDIN_FILENO], STDIN_FILENO);
	dup2(std_fd[STDOUT_FILENO], STDOUT_FILENO);
	close(std_fd[STDIN_FILENO]);
	close(std_fd[STDOUT_FILENO]);
	wait_procs(data->pipes);
}