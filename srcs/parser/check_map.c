/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:10:47 by adupin            #+#    #+#             */
/*   Updated: 2024/02/01 18:22:47 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_all_lines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr("01NSEWDT \t\r", map[i][j]))
				return (ft_error("Invalid character in the map"));
			j++;
		}
		i++;
	}
	return (0);
}

static void	assign_dir(char c, t_player *player) //seems logical may need to check
{
	player->dir_x = 0;
	player->dir_y = 0;
	if (c == 'N')
		player->dir_y = -1;
	else if (c == 'S')
		player->dir_y = 1;
	else if (c == 'W')
		player->dir_x = -1;
	else if (c == 'E')
		player->dir_x = 1;
}

static int	check_player_position(char **map, t_player *player)
{
	int	i;
	int	j;

	i = -1;
	player->pos_x = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NESW", map[i][j]))
			{
				if (player->pos_x)
					return (ft_error("More than one player on the map"));
				//probably need to change the structure of the function
				player->pos_x = j + 0.5;
				player->pos_y = i + 0.5;
				assign_dir(map[i][j], player);
				map[i][j] = '0';
			}
		}
	}
	if (!player->pos_x)
		return (ft_error("No player on the map"));
	return (0);
}

static int	check_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEWD0", map[i][j])
				&& ((i == 0 || j > (int) ft_strlen(map[i - 1])
					|| !ft_strchr("NSEWD01T", map[i - 1][j]))
				|| (!map[i + 1] || j > (int) ft_strlen(map[i + 1])
					|| !ft_strchr("NSEWD01T", map[i + 1][j]))
				|| (j == 0 || !ft_strchr("NSEWD01T", map[i][j - 1]))
				|| (!map[i][j + 1] || !ft_strchr("NSEWD01T", map[i][j + 1]))))
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
	if (check_player_position(data->map, &data->player))
		return (1);
	if (check_map_closed(data->map))
		return (1);
	return (0);
}
