/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:49:56 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/23 13:37:32 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "inc/minishell.h"

void ft_free(void *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
        ptr = NULL;
    }
}

static char	*join_str(char *str1, char *str2)
{
	char	*tmp;

	if (str2 == NULL)
		return (str1);
	if (str1 == NULL)
		return (ft_strdup(str2));
	tmp = str1;
	str1 = ft_strjoin(tmp, str2);
	ft_free(tmp);
	return (str1);
}

void	ft_err(char *message, char *detail)
{
    char *str;

    str = ft_strdup("minishell: ");
    str = join_str(str, message);
    str = join_str(str, ": ");
    str = join_str(str, detail);
    
    ft_putendl_fd(str, STDERR_FILENO);
    ft_free(str);
}