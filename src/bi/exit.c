/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:37:34 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/09/14 22:37:34 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO: TO BE DONE AT THE END OF THE PROJECT 

int msh_exit(t_tree *tree, t_env *env)
{
    tree_delete(tree);
    del_env(env);
    return (EXIT_SUCCESS);
}
