/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:26:34 by adupin            #+#    #+#             */
/*   Updated: 2024/01/31 15:39:15 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

// does transparency
void	mlx_true_pixel_put_img(t_img_info *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

// skips transparency
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

	if (!src || !dest)
		return ;
	j = 0;
	while (j < src->img_height)
	{
		if (y + j >= 0 && y + j < dest->img_height)
		{
			i = 0;
			while (i < src->img_width)
			{
				if (x + i >= 0 && x + i < dest->img_width)
					mlx_pixel_put_img(dest, x + i, y + j,
						get_pixel_color(src, i, j));
				i++;
			}
		}
		j++;
	}
}

/*
ways to reduce arguments:
- use an int array
- make a new struct for this and the print_rect functions
- make 'color' a static, call the function twice, 1: to set 'color' 2: for real.
	'print_rect' would need two.
- make 'color' a variable in a struct. 'data' isn't passed, so in every 'img'?
	'print_rect' would need two again.
- merge 'start' and 'end' into one int. with bitshifting or good old math
	e.g. '11112222' x = 1111 (int/10000), y = 2222 (int%10000)
	this effectively puts a max of 9999 on the coordinates (enough for 8k res)
*/
void	print_line(t_img_info *img, int x, int start, int end, int color)
{
	while (start < end)
	{
		mlx_pixel_put_img(img, x, start, color);
		start++;
	}
}

// same here but worse
void	print_rect(t_img_info *img, int x, int y, int width, int height, int color)
{
	while (width--)
	{
		print_line(img, x, y, y + height, color);
		x++;
	}
}
