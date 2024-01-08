/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:10:47 by adupin            #+#    #+#             */
/*   Updated: 2024/01/08 16:19:34 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \t\r", line[i]))
			return (ft_error("Invalid character in the map"));
		i++;
	}
	return (0);
}

int	check_all_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (check_line(map[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_player_position(char **map)
{
	int	i;
	int	j;
	int	nb_player;

	i = 0;
	nb_player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				nb_player++;
			j++;
		if (nb_player > 1)
			return (ft_error("Too many players in the map"));
		}
		i++;
	}
	if (nb_player == 0)
		return (ft_error("No player in the map"));
	return (0);
}

int	check_map_closed(char **map)
{
	int	i;
	int	j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW0", map[i][j])
				&& ((i == 0 || !ft_strchr("NSEW01", map[i - 1][j]))
				|| (!map[i + 1][j] || !ft_strchr("NSEW01", map[i + 1][j]))
				|| (j == 0 || !ft_strchr("NSEW01", map[i][j - 1]))
				|| (!map[i][j + 1] || !ft_strchr("NSEW01", map[i][j + 1]))))
					return (ft_error("Map is not closed"));
			j++;
		}
		i++;
	}
	return (0);
}

//return 1 if error, 0 if ok
int	check_map(t_data *data)
{
	if (check_all_lines(data->map))
		return (1);
	if (check_player_position(data->map))
		return (1);
	if (check_map_closed(data->map))
		return (1);
	return (0);
}
