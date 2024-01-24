/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:40:35 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/22 19:46:07 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_bi	*get_bi(char *cmd)
{
	if (ft_strequ(cmd, "echo"))
		return (msh_echo);
	else if (ft_strequ(cmd, "pwd"))
		return (msh_pwd);
	else if (ft_strequ(cmd, "env"))
		return (msh_env);
	else if (ft_strequ(cmd, "export"))
		return (msh_export);
	else if (ft_strequ(cmd, "unset"))
		return (msh_unset);
	else if (ft_strequ(cmd, "exit"))
		return (msh_exit);
	else if (ft_strequ(cmd, "cd"))
		return (msh_cd);
	return (NULL);
}
