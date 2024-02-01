/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:01 by adupin            #+#    #+#             */
/*   Updated: 2024/02/01 18:18:51 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	img_to_addr(t_img_info *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static void	all_img_to_addr(t_data *data)
{
	img_to_addr(data->north_img);
	img_to_addr(data->south_img);
	img_to_addr(data->west_img);
	img_to_addr(data->east_img);
	img_to_addr(data->door_img);
	img_to_addr(data->target_img);
	img_to_addr(data->torch_img);
	img_to_addr(data->torch_img + 1);
	img_to_addr(data->torch_img + 2);
	img_to_addr(data->torch_img + 3);
	img_to_addr(data->gun_img);
	img_to_addr(data->gun_img + 1);
}

int	setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("Mlx init failed"));
	if (malloc_img(data))
		return (ft_error("Malloc failed"));
	if (setup_textures(data))
		return (free_img(data), 1);
	all_img_to_addr(data);
	revert_all_img(data);
	data->mlx_win = mlx_new_window(data->mlx_ptr,
			WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->mlx_win)
		return (destroy_textures(data), free_img(data),
			ft_error("Mlx window init failed"));
	//need to check if protection is good
		// looks good to me ^^
	return (0);
}
