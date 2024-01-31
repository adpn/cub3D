/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:39:50 by adupin            #+#    #+#             */
/*   Updated: 2024/01/31 16:02:06 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Return 1 malloc fails, 2 if bad input
static int	assign_wall(char **wall, char **tab)
{
	int	i;

	i = 0;
	if (*wall)
		return (ft_error("Texture path already assigned"));
	while (tab[i])
		i++;
	if (i != 2)
		return (ft_error("Wrong number of informations"));
	*wall = ft_strdup(tab[1]);
	if (!*wall)
		return (ft_error("Malloc failed"));
	return (0);
}

static int	which_value(t_data *data, char **tab)
{
	int	len;

	len = ft_strlen(tab[0]);
	if (!ft_strncmp("NO", tab[0], len))
		return (assign_wall(&data->parser.north, tab));
	else if (!ft_strncmp("SO", tab[0], len))
		return (assign_wall(&data->parser.south, tab));
	else if (!ft_strncmp("EA", tab[0], len))
		return (assign_wall(&data->parser.east, tab));
	else if (!ft_strncmp("WE", tab[0], len))
		return (assign_wall(&data->parser.west, tab));
	else if (!ft_strncmp("D", tab[0], len))
		return (assign_wall(&data->parser.door, tab));
	else if (!ft_strncmp("F", tab[0], len))
		return (assign_color(data->parser.floor_rgb, tab));
	else if (!ft_strncmp("C", tab[0], len))
		return (assign_color(data->parser.ceiling_rgb, tab));
	else
		return (ft_error("Wrong or missing element"));
}

static int	assign_conf(t_data *data, char *line)
{
	char	**tab;
	int		i;

	tab = ft_split_charset(line, " \t\r");
	if (!tab)
		return (1);
	i = which_value(data, tab);
	ft_free_split(tab);
	return (i);
}

int	get_configuration(t_data *data, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (ft_error("Wrong or missing element"));
		if (ft_strchr(line, '\n'))
			ft_strchr(line, '\n')[0] = '\0';
		if (line[0] != '\0')
		{
			if (assign_conf(data, line))
				return (free(line), 1);
		}
		free(line);
		if (data->parser.north && data->parser.south && data->parser.east
			&& data->parser.west && data->parser.door
			&& data->parser.ceiling_rgb[0] != -1
			&& data->parser.floor_rgb[0] != -1)
			return (0);
	}
	return (0);
}
