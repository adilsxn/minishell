/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:23:24 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 22:23:24 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdlib.h>
/*NOTE: In short the inverse of export
 * if name is a var or function they are unset(meaning what? their
 * value is deleted or in the case of funcs they become unaccessible?)*/

int msh_bi_unset (void *env, char *name)
{

    return (EXIT_SUCCESS);
}

