/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:01 by adupin            #+#    #+#             */
/*   Updated: 2024/01/15 10:42:05 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

//i = 4 -> destroy all textures, otherwise destroy until the ith texture
void	destroy_textures(t_data *data, int i)
{
	if (i >= 1)
		mlx_destroy_image(data->mlx_ptr, data->north_img->img);
	if (i >= 2)
		mlx_destroy_image(data->mlx_ptr, data->south_img->img);
	if (i >= 3)
		mlx_destroy_image(data->mlx_ptr, data->west_img->img);
	if (i >= 4)
		mlx_destroy_image(data->mlx_ptr, data->east_img->img);
}

int	setup_textures(t_data *data)
{
	data->north_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->north, &data->north_img->img_width,
			&data->north_img->img_height);
	if (!data->north_img->img)
		return (1);
	data->south_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->south, &data->south_img->img_width,
			&data->south_img->img_height);
	if (!data->south_img->img)
		return (destroy_textures(data, 1), 1);
	data->west_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->west, &data->west_img->img_width,
			&data->west_img->img_height);
	if (!data->west_img->img)
		return (destroy_textures(data, 2), 1);
	data->east_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->east, &data->east_img->img_width,
			&data->east_img->img_height);
	if (!data->east_img->img)
		return (destroy_textures(data, 3), 1);
	return (0);
}

void	img_to_addr(t_img_info *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
}

int	setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("Mlx init failed"));
	data->north_img = malloc(sizeof(t_img_info)); //to put in a function
	data->south_img = malloc(sizeof(t_img_info));
	data->west_img = malloc(sizeof(t_img_info));
	data->east_img = malloc(sizeof(t_img_info));
	if (setup_textures(data))
		return (ft_error("Can't load one of the textures"));
	img_to_addr(data->north_img);
	img_to_addr(data->south_img);
	img_to_addr(data->west_img);
	img_to_addr(data->east_img);
	return (0);
}
