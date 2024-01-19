/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:01 by adupin            #+#    #+#             */
/*   Updated: 2024/01/19 11:46:50 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

//i = 4 -> destroy all textures, otherwise destroy until the ith texture
void	destroy_textures(t_data *data)
{	
	if (data->north_img->img)
		mlx_destroy_image(data->mlx_ptr, data->north_img->img);
	if (data->south_img->img)
		mlx_destroy_image(data->mlx_ptr, data->south_img->img);
	if (data->west_img->img)
		mlx_destroy_image(data->mlx_ptr, data->west_img->img);
	if (data->east_img->img)
		mlx_destroy_image(data->mlx_ptr, data->east_img->img);
}

int	setup_textures(t_data *data)
{
	data->north_img->img = NULL;
	data->south_img->img = NULL;
	data->west_img->img = NULL;
	data->east_img->img = NULL;
	data->north_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->input->north, &data->north_img->img_width,
			&data->north_img->img_height);
	if (!data->north_img->img)
		return (1);
	data->south_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->input->south, &data->south_img->img_width,
			&data->south_img->img_height);
	if (!data->south_img->img)
		return (destroy_textures(data), 1);
	data->west_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->input->west, &data->west_img->img_width,
			&data->west_img->img_height);
	if (!data->west_img->img)
		return (destroy_textures(data), 1);
	data->east_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->input->east, &data->east_img->img_width,
			&data->east_img->img_height);
	if (!data->east_img->img)
		return (destroy_textures(data), 1);
	return (0);
}

void	img_to_addr(t_img_info *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
}

int	malloc_img(t_data *data)
{
	data->north_img = malloc(sizeof(t_img_info));
	if (!data->north_img)
		return (1);
	data->south_img = malloc(sizeof(t_img_info));
	if (!data->south_img)
		return (1);
	data->west_img = malloc(sizeof(t_img_info));
	if (!data->west_img)
		return (1);
	data->east_img = malloc(sizeof(t_img_info));
	if (!data->east_img)
		return (1);
	return (0);	
}

void	free_img(t_data *data)
{
	if (data->north_img)
		free(data->north_img);
	if (data->south_img)
		free(data->south_img);
	if (data->west_img)
		free(data->west_img);
	if (data->east_img)
		free(data->east_img);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	color_to_rgb(int color, int tgrb[4])
{
	tgrb[0] = (color & (0xFF << 24)) >> 24;
	tgrb[1] = (color & (0xFF << 16)) >> 16;
	tgrb[2] = (color & (0xFF << 8)) >> 8;
	tgrb[3] = (color & (0xFF));
}

int	setup(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("Mlx init failed"));
	if (malloc_img(data))
		return (free_img(data), ft_error("Malloc failed"));
	if (setup_textures(data))
		return (free_img(data), ft_error("Can't load one of the textures"));
	img_to_addr(data->north_img);
	img_to_addr(data->south_img);
	img_to_addr(data->west_img);
	img_to_addr(data->east_img);
	data->mlx_win = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D"); //may need to protect and change size
	
	return (0);
}
