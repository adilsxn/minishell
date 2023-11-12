/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:39:49 by matilde           #+#    #+#             */
/*   Updated: 2023/11/11 18:58:45 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "minishell.h"

typedef struct s_global
{
	int	error_nb;
	int	in_cmd;
}t_global;

t_global    g_global;

#endif