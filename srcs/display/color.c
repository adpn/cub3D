/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:23:57 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/05 14:36:08 by bvercaem         ###   ########.fr       */
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
