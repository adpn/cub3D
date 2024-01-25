/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:38:34 by adupin            #+#    #+#             */
/*   Updated: 2024/01/25 15:26:32 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clear_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

static char	*skip_empty_line(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		if (!line[0])
			return (free(line), NULL);
		if (line[0] != '\n')
			return (line);
		free(line);
	}
	return (NULL);
}

static int	add_line_to_map(t_data *data, char *line)
{
	int		nb_lines;
	int		i;
	char	**tab;
	char	**new_tab;

	nb_lines = 0;
	while (data->map[nb_lines])
		nb_lines++;
	new_tab = malloc((nb_lines + 2) * sizeof(char *));
	if (!new_tab)
		return (ft_error("Malloc failed"));
	tab = data->map;
	i = 0;
	while (i < nb_lines)
	{
		new_tab[i] = tab[i];
		i++;
	}
	if (ft_strchr(line, '\n'))
		ft_strchr(line, '\n')[0] = '\0';
	new_tab[i] = line;
	new_tab[i + 1] = NULL;
	free(tab);
	data->map = new_tab;
	data->map_size++;
	return (0);
}

static int	fill_map(t_data *data, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		if (line[0] == '\n')
			return (free(line), ft_error("Empty line in map"));
		if (add_line_to_map(data, line))
			return (free(line), 1);
	}
}

int	get_map(t_data *data, int fd)
{
	char	*line;

	data->map_size = 0;
	line = skip_empty_line(fd);
	if (!line)
		return (ft_error("Map is missing"));
	data->map = malloc(sizeof(char *));
	if (!data->map)
		return (free(line), ft_error("Malloc failed"));
	data->map[0] = NULL;
	if (add_line_to_map(data, line))
		return (clear_map(data), 1);
	if (fill_map(data, fd))
		return (clear_map(data), 1);
	return (0);
}
