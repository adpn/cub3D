/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:01 by adupin            #+#    #+#             */
/*   Updated: 2024/01/30 18:55:28 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

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
	if (data->door_img->img)
		mlx_destroy_image(data->mlx_ptr, data->door_img->img);
	if (data->torch_img->img)
		mlx_destroy_image(data->mlx_ptr, data->torch_img->img);
	if ((data->torch_img + 1)->img)
		mlx_destroy_image(data->mlx_ptr, (data->torch_img + 1)->img);
	if ((data->torch_img + 2)->img)
		mlx_destroy_image(data->mlx_ptr, (data->torch_img + 2)->img);
	if ((data->torch_img + 3)->img)
		mlx_destroy_image(data->mlx_ptr, (data->torch_img + 3)->img);
	if (data->gun_img->img)
		mlx_destroy_image(data->mlx_ptr, data->gun_img->img);
	if ((data->gun_img + 1)->img)
		mlx_destroy_image(data->mlx_ptr, (data->gun_img + 1)->img);
}

static void	do_texture(t_data *data, t_img_info *img, char *input, int *err)
{
	img->img = NULL;
	if (*err)
		return ;
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, input, &img->img_width, &img->img_height);
	if (!img->img)
		*err = 1;
}

int	setup_textures(t_data *data)
{
	int	err;

	err = 0;
	do_texture(data, data->north_img, data->parser->north, &err);
	do_texture(data, data->south_img, data->parser->south, &err);
	do_texture(data, data->west_img, data->parser->west, &err);
	do_texture(data, data->east_img, data->parser->east, &err);
	do_texture(data, data->door_img, data->parser->door, &err);
	do_texture(data, data->torch_img, "textures/doom_torch_1.xpm", &err);
	do_texture(data, data->torch_img + 1, "textures/doom_torch_2.xpm", &err);
	do_texture(data, data->torch_img + 2, "textures/doom_torch_3.xpm", &err);
	do_texture(data, data->torch_img + 3, "textures/doom_torch_4.xpm", &err);
	do_texture(data, data->gun_img, "textures/wolf_gun_idle.xpm", &err);
	do_texture(data, data->gun_img + 1, "textures/wolf_gun_shoot.xpm", &err);
	if (err)
		return (destroy_textures(data), 1);
	return (0);
}

void	img_to_addr(t_img_info *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
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
	if (data->door_img)
		free(data->door_img);
	if (data->torch_img)
		free(data->torch_img);
	if (data->gun_img)
		free(data->gun_img);
}

static void	do_malloc_img(t_img_info **img, int size, int *err)
{
	*img = NULL;
	if (*err)
		return ;
	*img = malloc(sizeof(t_img_info) * size);
	if (!*img)
		*err = 1;
}

int	malloc_img(t_data *data)
{
	int	err;

	err = 0;
	do_malloc_img(&data->north_img, 1, &err);
	do_malloc_img(&data->south_img, 1, &err);
	do_malloc_img(&data->west_img, 1, &err);
	do_malloc_img(&data->east_img, 1, &err);
	do_malloc_img(&data->door_img, 1, &err);
	do_malloc_img(&data->torch_img, 4, &err);
	do_malloc_img(&data->gun_img, 2, &err);
	if (err)
		return (1);
	return (0);
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

void	revert_img(t_img_info *img)
{
	int	i;
	int	j;
	int tmp;

	j = 0;
	while (j < img->img_height)
	{
		i = 0;
		while (i < img->img_width / 2)
		{
			tmp = get_pixel_color(img, i, j);
			mlx_pixel_put_img(img, i, j, get_pixel_color(img, img->img_width - 1 - i, j));
			mlx_pixel_put_img(img, img->img_width - 1 - i, j, tmp);
			i++;
		}
		j++;
	}
}

void	all_img_to_addr(t_data *data)
{
	img_to_addr(data->north_img);
	img_to_addr(data->south_img);
	img_to_addr(data->west_img);
	img_to_addr(data->east_img);
	img_to_addr(data->door_img);
	img_to_addr(data->torch_img);
	img_to_addr(data->torch_img + 1);
	img_to_addr(data->torch_img + 2);
	img_to_addr(data->torch_img + 3);
	img_to_addr(data->gun_img);
	img_to_addr(data->gun_img + 1);
}

void	revert_all_img(t_data *data)
{
	revert_img(data->north_img);
	revert_img(data->south_img);
	revert_img(data->west_img);
	revert_img(data->east_img);
	revert_img(data->door_img);
	revert_img(data->torch_img);
	revert_img(data->torch_img + 1);
	revert_img(data->torch_img + 2);
	revert_img(data->torch_img + 3);
	revert_img(data->gun_img);
	revert_img(data->gun_img + 1);
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
	all_img_to_addr(data);
	revert_all_img(data);
	data->mlx_win = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!data->mlx_win)
		return (destroy_textures(data), free_img(data), ft_error("Mlx window init failed"));
	//need to check if protection is good
	return (0);
}
