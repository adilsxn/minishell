/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:30:37 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/07/30 20:30:37 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_new_line_idx(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static char	*line_cleaner(char **string)
{
	char	*line;
	char	*it;
	int		i;

	if (!*string || **string == '\0')
		return (NULL);
	i = get_new_line_idx(*string);
	if (ft_strchr(*string, '\n'))
	{
		line = ft_substr(*string, 0, i + 1);
		it = ft_substr(*string, i + 1, ft_strlen(*string) - i - 1);
		free(*string);
		*string = it;
		if (**string != '\0')
			return (line);
	}
	else
		line = ft_strdup(*string);
	free(*string);
	*string = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;
	char		*it;
	int			readsize;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	readsize = read(fd, line, BUFFER_SIZE);
	while (readsize > 0)
	{
		line[readsize] = '\0';
		if (!buffer[fd])
			buffer[fd] = ft_strdup("");
		it = ft_strjoin(buffer[fd], line);
		free(buffer[fd]);
		buffer[fd] = it;
		if (ft_strchr(buffer[fd], '\n'))
			break ;
		readsize = read(fd, line, BUFFER_SIZE);
	}
	free(line);
	return (line_cleaner(&buffer[fd]));
}
