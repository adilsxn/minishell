/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:10:04 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/11 13:10:04 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_bin(char **av, t_tree *tree, t_env *env)
{
	pid_t	pid;
	int		sts;
	int		ret;
	char	*cmdpath;

	sts = 0;
	ret = 0;
	cmdpath = cmd_finder(tree, env);
	if (cmdpath == NULL)
		perror("command not found\n");
	pid = fork();
	if (pid == -1)
		perror("Error: fork failed\n");
	else if (pid == 0)
	{
		if (execve(cmdpath, av, NULL) == -1)
			perror("Error: execve failed\n");
		free(cmdpath);
	}
	waitpid(pid, &sts, 0);
	if (WIFEXITED(sts))
		ret = WEXITSTATUS(sts);
	else
		ret = WIFSIGNALED(sts);
	return (ret);
}

static bool	is_builtin(char *str)
{
    if (ft_strequ(str, "echo"))
        return (true);
    if (ft_strequ(str, "cd"))
        return (true);
    if (ft_strequ(str, "pwd"))
        return (true);
    if (ft_strequ(str, "export"))
        return (true);
    if (ft_strequ(str, "unset"))
        return (true);
    if (ft_strequ(str, "env"))
        return (true);
    if (ft_strequ(str, "exit"))
        return (true);
    return (false);
}

void	exec_cmd(t_tree *tree, t_env *env)
{
	int		status;
	char	**argv;

	argv = build_av(tree);
	status = 0;
	if (is_builtin(tree->token))
		status = exec_bi(argv, tree, env);
	else
		status = exec_bin(argv, tree, env);
	set_env(&env, "?", ft_itoa(status));
}
