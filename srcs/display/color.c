/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:23:57 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/05 14:10:10 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	get_pixel_color(t_img_info *img, int x, int y)
{
	char	*color;

	color = img->addr;
	color += (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	return (*(int *)color);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// not in use
// void	color_to_rgb(int color, int tgrb[4])
// {
// 	tgrb[0] = (color & (0xFF << 24)) >> 24;
// 	tgrb[1] = (color & (0xFF << 16)) >> 16;
// 	tgrb[2] = (color & (0xFF << 8)) >> 8;
// 	tgrb[3] = (color & (0xFF));
// }
