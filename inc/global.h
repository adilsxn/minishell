/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:39:49 by matilde           #+#    #+#             */
/*   Updated: 2023/11/12 19:19:06 by acuva-nu         ###   ########.fr       */
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
