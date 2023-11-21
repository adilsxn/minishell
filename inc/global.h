/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matilde <matilde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:39:49 by matilde           #+#    #+#             */
/*   Updated: 2023/11/12 21:11:16 by matilde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct s_global
{
	int	error_nb;
	int	in_cmd;
}t_global;

static t_global    g_global;

#endif
