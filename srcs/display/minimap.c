/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:41:15 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/01 18:42:57 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	clear_minimap(t_data *data)
{
	if (!data->minimap)
		return ;
	mlx_destroy_image(data->mlx_ptr, data->minimap->img);
	free(data->minimap);
	data->minimap = NULL;
}

int	generate_minimap(t_data *data)
{
	data->minimap = malloc(sizeof(t_img_info));
	if (!data->minimap)
		return (ft_error("Malloc failed"));
	data->minimap->img = mlx_new_image(data->mlx_ptr, M_TI * (MAP_SIZE + 2),
			M_TI * (MAP_SIZE + 2));
	if (!data->minimap->img)
		return (free(data->minimap), ft_error("Mlx new image failed"));
	data->minimap->img_width = M_TI * (MAP_SIZE + 2);
	data->minimap->img_height = M_TI * (MAP_SIZE + 2);
	img_to_addr(data->minimap);
	if (!data->minimap)
		return (clear_minimap(data), ft_error("Mlx get address failed"));
	print_rect(data->minimap, 0, 0, M_TI, M_TI * (MAP_SIZE + 2), C_WHITE);
	print_rect(data->minimap, M_TI * (MAP_SIZE + 1), 0, M_TI,
		M_TI * (MAP_SIZE + 2), C_WHITE);
	print_rect(data->minimap, M_TI, 0, MAP_SIZE * M_TI, M_TI, C_WHITE);
	print_rect(data->minimap, M_TI, M_TI * (MAP_SIZE + 1),
		MAP_SIZE * M_TI, M_TI, C_WHITE);
	return (0);
}

// can't print pure black (because of a shortcut)
static void	put_minimap_tile(t_data *data, char obj, int i, int j)
{
	int	color;

	color = 0;
	if (obj == '1')
		color = create_trgb(0, 150, 150, 150);
	else if (obj == 'T')
		color = create_trgb(0, 250, 30, 60);
	else if (obj == 'D')
		color = create_trgb(0, 30, 100, 200);
	if (color)
		print_rect(data->minimap, j * M_TI + M_TI,
			i * M_TI + M_TI, M_TI, M_TI, color);
}

static void	parse_minimap(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int) data->player.pos_x - ((MAP_SIZE - 1) / 2);
	y = (int) data->player.pos_y - ((MAP_SIZE - 1) / 2);
	i = MAP_SIZE;
	while (i--)
	{
		j = MAP_SIZE;
		while (j--)
		{
			if (x + j < 0 || y + i < 0 || y + i >= data->map_size
				|| x + j >= (int) ft_strlen(data->map[y + i]))
				continue ;
			put_minimap_tile(data, data->map[y + i][x + j], i, j);
		}
	}
}

void	update_minimap(t_data *data)
{
	float	x;
	float	y;
	int		i;

	print_rect(data->minimap, M_TI, M_TI, MAP_SIZE * M_TI, MAP_SIZE * M_TI, 0);
	parse_minimap(data);
	x = (MAP_SIZE + 2) * M_TI / 2;
	y = x;
	i = M_TI;
	while (i--)
	{
		x += data->player.dir_x;
		y += data->player.dir_y;
		mlx_pixel_put_img(data->minimap, (int) rint(x), (int) rint(y), C_WHITE);
	}
	print_rect(data->minimap, (M_TI * (MAP_SIZE + 1)) / 2,
		(M_TI * (MAP_SIZE + 1)) / 2, M_TI, M_TI, create_trgb(0, 30, 200, 100));
}
