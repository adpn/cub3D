/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:20:30 by adupin            #+#    #+#             */
/*   Updated: 2024/01/03 12:24:47 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_all(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{			
		buffer[i] = '\0';
		i++;
	}
	return (NULL);
}

static int	read_next(char *buffer, int fd)
{
	int		size;
	int		i;

	i = 0;
	if (ft_strlen(buffer) == 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free_all(buffer);
			return (-1);
		}
		buffer[size] = '\0';
		return (size);
	}
	return (ft_strlen(buffer));
}

static char	*ft_copymalloc(char	*str, int size)
{
	char	*new;

	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	gnl_strlcpy(new, str, size + 1);
	return (new);
}

static char	*find_line(char *buffer, int fd)
{
	int		i;
	char	*line;
	char	*temp;

	line = NULL;
	i = gnl_strchr(buffer, '\n');
	while (i == -1)
	{
		line = gnl_join(line, buffer);
		if (!line)
			return (free_all(buffer));
		buffer[0] = '\0';
		if (read_next(buffer, fd) <= 0)
			return (line);
		i = gnl_strchr(buffer, '\n');
	}
	temp = ft_copymalloc(buffer, i + 1);
	if (!temp)
		return (free_all(buffer));
	line = gnl_join(line, temp);
	free(temp);
	if (!line)
		return (free_all(buffer));
	gnl_strlcpy(&buffer[0], &buffer[i + 1], BUFFER_SIZE + 1);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (free_all(buffer));
	if (read_next(buffer, fd) <= 0 && buffer[0] == '\0')
		return (line);
	line = find_line(buffer, fd);
	if (!line)
		return (free_all(buffer));
	return (line);
}
