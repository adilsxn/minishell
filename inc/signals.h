/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:53:46 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/16 08:53:46 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h>

void setup_sgnl(void(*handler)(int), int signal);

void sgnl_child(int signal);

void sgnl_parent(int signal);

void sgnl_prompt(int signal);

void sgnl_hd_child(int signal);

void sgnl_hd_parent(int signal);

#endif
