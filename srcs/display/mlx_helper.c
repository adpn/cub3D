/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:26:34 by adupin            #+#    #+#             */
/*   Updated: 2024/01/30 19:44:11 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	get_pixel_color(t_img_info *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	return (*(int *)color);
}

// does transparency
void	mlx_true_pixel_put_img(t_img_info *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	mlx_pixel_put_img(t_img_info *img, int x, int y, int color)
{
	char	*pixel;

	if ((color >> 24 & 0xFF) >= 230)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

// coordinates correspond to dest
void	mlx_img_put_img(t_img_info *src, t_img_info *dest, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < src->img_height)
	{
		if (y + j >= 0 && y + j < dest->img_height)
		{
			i = 0;
			while (i < src->img_width)
			{
				if (x + i >= 0 && x + i < dest->img_width)
					mlx_pixel_put_img(dest, x + i, y + j, get_pixel_color(src, i, j));
				i++;
			}
		}
		j++;
	}
}

void	print_line(t_img_info *img, int x, int start, int end, int color)
{
	while (start < end)
	{
		mlx_pixel_put_img(img, x, start, color);
		start++;
	}
}

void	print_rect(t_img_info *img, int x, int y, int width, int height, int color)
{
	while (width--)
	{
		print_line(img, x, y, y + height, color);
		x++;
	}
}
