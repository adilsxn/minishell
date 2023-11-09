/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:39:49 by matilde           #+#    #+#             */
/*   Updated: 2023/11/09 11:42:34 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct s_global
{
	int	error_nb;
	//int	stop_heredoc;
	//int	in_cmd;
	//int	in_heredoc;
}t_global;

t_global    g_global;

#endif