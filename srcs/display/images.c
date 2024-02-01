/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:18:13 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/01 18:17:08 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static void	revert_img(t_img_info *img)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	while (j < img->img_height)
	{
		i = 0;
		while (i < img->img_width / 2)
		{
			tmp = get_pixel_color(img, i, j);
			mlx_true_pixel_put_img(img, i, j,
				get_pixel_color(img, img->img_width - 1 - i, j));
			mlx_true_pixel_put_img(img, img->img_width - 1 - i, j, tmp);
			i++;
		}
		j++;
	}
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
	if (data->target_img)
		free(data->target_img);
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
	do_malloc_img(&data->target_img, 1, &err);
	do_malloc_img(&data->torch_img, 4, &err);
	do_malloc_img(&data->gun_img, 2, &err);
	if (err)
		return (free_img(data), 1);
	return (0);
}
