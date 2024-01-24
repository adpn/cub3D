/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:29 by adupin            #+#    #+#             */
/*   Updated: 2024/01/24 17:04:32 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "cub3d.h"

int	get_pixel_color(t_img_info *img, int x, int y);
void	mlx_pixel_put_img(t_img_info *img, int x, int y, int color);
void	img_to_addr(t_img_info *img);
int		update(t_data *data);

void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);
void	turn_right(t_data *data);
void	turn_left(t_data *data);
void	look_left(t_data *data, float x);
void	look_right(t_data *data, float x);

int	keydown(int keycode, t_data *data);
int	keyup(int keycode, t_data *data);
int mouse_move(int x, int y, t_data *data);
int	send_change(t_data *data);
int	end(t_data *data);
int mouse_click(int button, int x, int y, t_data *data);
#endif