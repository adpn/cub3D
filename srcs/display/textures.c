/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:21:11 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/05 14:16:16 by bvercaem         ###   ########.fr       */
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
	if (data->target_img->img)
		mlx_destroy_image(data->mlx_ptr, data->target_img->img);
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
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, input,
			&img->img_width, &img->img_height);
	if (!img->img)
	{
		*err = 1;
		ft_putstr_fd("Error\nCan't load the texture '", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd("'", 2);
	}
}

// prints its own error
int	setup_textures(t_data *data)
{
	int	err;

	err = 0;
	do_texture(data, data->north_img, data->parser.north, &err);
	do_texture(data, data->south_img, data->parser.south, &err);
	do_texture(data, data->west_img, data->parser.west, &err);
	do_texture(data, data->east_img, data->parser.east, &err);
	do_texture(data, data->door_img, data->parser.door, &err);
	do_texture(data, data->target_img, "textures/iron_cross.xpm", &err);
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
