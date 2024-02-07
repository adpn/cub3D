/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_shapes_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:46:07 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/05 14:36:32 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

// fills two spots of 'a'
// 'b' == NULL: fills [0] and [1]
// 'b' != NULL: fills [0],[1] with 'b' and then [2] and [3]
int	*fill_print_array(int *a, int *b, int arg1, int arg2)
{
	int	i;

	i = 0;
	if (b)
	{
		a[0] = b[0];
		a[1] = b[1];
		i = 2;
	}
	a[i] = arg1;
	a[i + 1] = arg2;
	return (a);
}

void	print_line(t_img_info *img, int *x_y, int y_end, int color)
{
	int	start;

	start = x_y[1];
	while (start < y_end)
	{
		mlx_pixel_put_img(img, x_y[0], start, color);
		start++;
	}
}

// _w_ = width, _h = height
void	print_rect(t_img_info *img, int *x_y_w_h, int color)
{
	int	i;
	int	x_y[2];

	x_y[0] = x_y_w_h[0];
	x_y[1] = x_y_w_h[1];
	i = 0;
	while (i < x_y_w_h[2])
	{
		print_line(img, x_y, x_y_w_h[1] + x_y_w_h[3], color);
		x_y[0]++;
		i++;
	}
}
