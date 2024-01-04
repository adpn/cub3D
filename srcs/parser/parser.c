/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:50:00 by adupin            #+#    #+#             */
/*   Updated: 2024/01/04 18:33:47 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
Line example:
F 220,     100, 1    0
tab = F/220,/100,/1/0
split = F 220/       100/ 1     0

F 220,100, 1 02
tab = F/220,100,/1/02

*/



void	init_value(t_data *data)
{
	data->path->north = NULL;
	data->path->south = NULL;
	data->path->west = NULL;
	data->path->east = NULL;
	data->ceiling_color[0] = -1;
	data->ceiling_color[1] = -1;
	data->ceiling_color[2] = -1;
	data->floor_color[0] = -1;
	data->floor_color[1] = -1;
	data->floor_color[2] = -1;
	data->map = NULL;
}
// Return 1 malloc fails, 2 if bad input
int	assign_wall(char **wall, char **tab)
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

int	which_value(t_data *data, char **tab)
{
	int	len;
	
	len = ft_strlen(tab[0]);
	if (!ft_strncmp("NO", tab[0], len))
		return (assign_wall(&data->path->north, tab));
	else if (!ft_strncmp("SO", tab[0], len))
		return (assign_wall(&data->path->south, tab));
	else if (!ft_strncmp("EA", tab[0], len))
		return (assign_wall(&data->path->east, tab));
	else if (!ft_strncmp("WE", tab[0], len))
		return (assign_wall(&data->path->west, tab));
	else if (!ft_strncmp("F", tab[0], len))
		return (assign_color(data->floor_color, tab));
	else if (!ft_strncmp("C", tab[0], len))
		return (assign_color(data->ceiling_color, tab));
	else
		return (ft_error("Wrong or missing element"));
}

int	assign_conf(t_data *data, char *line)
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
		if (line == NULL)
			return (ft_error("Wrong or missing element"));
		ft_strchr(line, '\n')[0] = '\0';
		if (line[0] != '\0')
		{
			if (assign_conf(data, line))
				return (free(line), 1);
		}
		free(line);	
		if (data->path->north && data->path->south && data->path->east
			&& data->path->west && data->ceiling_color[0] != -1
				&& data->floor_color[0] != -1)
			return (0);
	}
	return (0);
}

int	parser(t_data *data, int fd)
{
	init_value(data);
	if (get_configuration(data, fd))
		return (1);
	//get_map(data, fd);
	return (0);


}