/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:19:21 by wintoo            #+#    #+#             */
/*   Updated: 2025/10/17 20:03:53 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_memory(char **str)
{
	if (str && *str)
	{
		free (*str);
		*str = NULL;
	}
}

char	*read_file(int fd, char *stash, char *buffer)
{
	int		readbyte;
	char	*temp;

	readbyte = 1;
	while (readbyte > 0)
	{
		readbyte = read(fd, buffer, BUFFER_SIZE);
		if (readbyte == -1)
			return (free_memory(&stash), NULL);
		else if (readbyte == 0)
			break ;
		buffer[readbyte] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free_memory(&temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*set_nextline(char *line)
{
	size_t	i;
	char	*stash;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	stash = ft_strdup(line + i + 1);
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*newline;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free_memory(&stash);
		free_memory(&buffer);
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	newline = read_file(fd, stash, buffer);
	free_memory(&buffer);
	if (!newline)
		return (NULL);
	stash = set_nextline(newline);
	return (newline);
}
