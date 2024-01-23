/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 22:38:14 by acuva-nu          #+#    #+#             */
/*   Updated: 2024/01/23 09:48:05 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void	check_line_and_free(char *line, char *delim)
{
	if (line != NULL)
		free(line);
	else
		ft_err("here_doc received end-of-file, wanted", delim);
}

char	*get_delimiter(char *input, size_t *counter, char *quote)
{
	char	*delim;

	while ((is_redirect(input[*counter]) != 0))
		*counter += 1;
	while ((ft_isspace(input[*counter]) != 0))
		*counter += 1;
	if ((is_quote(input[*counter]) != 0)
		&& has_matching_quote(&(input[*counter])))
		*quote = input[*counter];
	delim = word(input, counter, 0);
	if (delim != NULL && (ft_strcmp(delim, "") == 0))
	{
		free(delim);
		return (NULL);
	}
	return (delim);
}

char	*turn_line_into_word(char *line)
{
	size_t	counter;

	counter = 0;
	return (word(line, &counter, 1));
}

char	*join_line(char *content, char *line, char quote)
{
	char	*temp;

	ft_asprintf(&temp, "%c%s\n%c", quote, line, quote);
	free(line);
	line = turn_line_into_word(temp);
	free(temp);
	ft_asprintf(&temp, "%s%s", content, line);
	free(content);
	free(line);
	return (temp);
}
