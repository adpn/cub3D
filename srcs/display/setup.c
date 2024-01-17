/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:01 by adupin            #+#    #+#             */
/*   Updated: 2024/01/17 14:07:30 by adupin           ###   ########.fr       */
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
		data->path->north, &data->north_img->img_width,
			&data->north_img->img_height);
	if (!data->north_img->img)
		return (1);
	data->south_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->south, &data->south_img->img_width,
			&data->south_img->img_height);
	if (!data->south_img->img)
		return (destroy_textures(data), 1);
	data->west_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->west, &data->west_img->img_width,
			&data->west_img->img_height);
	if (!data->west_img->img)
		return (destroy_textures(data), 1);
	data->east_img->img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->path->east, &data->east_img->img_width,
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

void	print_texture(t_data *data)
{
	int color;
	void	*img;

	img = mlx_new_image(data->mlx_ptr, 64, 64);
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			color = get_color(data->east_img, x, y);
			//printf("Color %i\n", color);
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, color);
		}
	}
	//mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img, 0, 0);
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
	
	printf("Ceiling color %i %i %i\n", data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	int	color = create_trgb(0, data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2]);
	printf("Color %i\n", color);
	int tgrb[4];
	color_to_rgb(color, tgrb);
	printf("Color after %i %i %i %i\n", tgrb[0], tgrb[1], tgrb[2], tgrb[3]);


	data->mlx_win = mlx_new_window(data->mlx_ptr, 64, 64, "Cub3D");
	print_texture(data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
