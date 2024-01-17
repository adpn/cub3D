/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/16 16:51:55 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	get_color(t_img_info *img, int x, int y)
{
	char	*color;

	color = img->addr + (y * img->line_length + (x * (img->bits_per_pixel / 8)));
	return (*(int *)color);
}