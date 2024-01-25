/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:29 by adupin            #+#    #+#             */
/*   Updated: 2024/01/25 15:21:32 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "cub3d.h"

int		generate_minimap(t_data *data);

int		get_pixel_color(t_img_info *img, int x, int y);
int		create_trgb(int t, int r, int g, int b);
void	mlx_pixel_put_img(t_img_info *img, int x, int y, int color);
void	print_line(t_img_info *img, int x, int start, int end, int color);
void	print_rect(t_img_info *img, int x, int y, int width, int height, int color);
void	img_to_addr(t_img_info *img);
int		update(t_data *data);
void	update_minimap(t_data *data);

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	turn_right(t_data *data);
void	turn_left(t_data *data);
#endif
