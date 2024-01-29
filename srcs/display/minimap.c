/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:41:15 by bvercaem          #+#    #+#             */
/*   Updated: 2024/01/29 14:45:28 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	generate_minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_img_info));
	if (!data->minimap)
		return (ft_error("Malloc failed"));
	data->minimap->img = mlx_new_image(data->mlx_ptr, MAP_TILE * (MAP_SIZE + 2),
			MAP_TILE * (MAP_SIZE + 2));
	if (!data->minimap->img)
		return (free(data->minimap), ft_error("Mlx new image failed"));
	data->minimap->img_width = MAP_TILE * (MAP_SIZE + 2);
	data->minimap->img_height = MAP_TILE * (MAP_SIZE + 2);
	img_to_addr(data->minimap);
	if (!data->minimap)
		return (mlx_destroy_image(data->mlx_ptr, data->minimap->img),
			free(data->minimap), ft_error("Mlx get address failed"));
	print_rect(data->minimap, 0, 0, MAP_TILE, MAP_TILE * (MAP_SIZE + 2),
		create_trgb(0, 250, 250, 250));
	print_rect(data->minimap, MAP_TILE * (MAP_SIZE + 1), 0, MAP_TILE,
		MAP_TILE * (MAP_SIZE + 2), create_trgb(0, 250, 250, 250));
	print_rect(data->minimap, MAP_TILE, 0, MAP_SIZE * MAP_TILE, MAP_TILE,
		create_trgb(0, 250, 250, 250));
	print_rect(data->minimap, MAP_TILE, MAP_TILE * (MAP_SIZE + 1),
		MAP_SIZE * MAP_TILE, MAP_TILE, create_trgb(0, 250, 250, 250));
	return (0);
}

void	clear_minimap(t_data *data)
{
	if (!data->minimap)
		return ;
	mlx_destroy_image(data->mlx_ptr, data->minimap->img);
	free(data->minimap);
	data->minimap = NULL;
}

static void	parse_minimap(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int) data->player->pos_x - ((MAP_SIZE - 1) / 2);
	y = (int) data->player->pos_y - ((MAP_SIZE - 1) / 2);
	i = MAP_SIZE;
	while (i--)
	{
		j = MAP_SIZE;
		while (j--)
		{
			if (x + j < 0 || y + i < 0 || y + i >= data->map_size
				|| x + j >= (int) ft_strlen(data->map[y + i]))
				continue ;
			if (data->map[y + i][x + j] == '1')
				print_rect(data->minimap, j * MAP_TILE + MAP_TILE,
					i * MAP_TILE + MAP_TILE, MAP_TILE, MAP_TILE,
					create_trgb(0, 150, 150, 150));
			else if (data->map[y + i][x + j] == 'D')
				print_rect(data->minimap, j * MAP_TILE + MAP_TILE,
					i * MAP_TILE + MAP_TILE, MAP_TILE, MAP_TILE,
					create_trgb(0, 30, 200, 100));
		}
	}
}

static void	add_player(t_data *data)
{
	float	x;
	float	y;
	int		i;

	x = (MAP_SIZE + 2) * MAP_TILE / 2;
	y = x;
	i = 6;
	while (i--)
	{
		x += data->player->dir_x;
		y += data->player->dir_y;
		mlx_pixel_put_img(data->minimap, (int) rint(x), (int) rint(y),
			create_trgb(0, 250, 250, 250));
	}
	print_rect(data->minimap, (MAP_TILE * (MAP_SIZE + 1)) / 2,
		(MAP_TILE * (MAP_SIZE + 1)) / 2,
		MAP_TILE, MAP_TILE, create_trgb(0, 250, 70, 70));
}

void	update_minimap(t_data *data)
{
	print_rect(data->minimap, MAP_TILE, MAP_TILE, MAP_SIZE * MAP_TILE,
		MAP_SIZE * MAP_TILE, 0);
	parse_minimap(data);
	add_player(data);
}
