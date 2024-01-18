/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:26:34 by adupin            #+#    #+#             */
/*   Updated: 2024/01/18 17:13:28 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	get_pixel_color(t_img_info *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	return (*(int *)color);
}

void	mlx_pixel_put_img(t_img_info *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

