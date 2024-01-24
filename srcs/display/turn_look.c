/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_look.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:53:43 by adupin            #+#    #+#             */
/*   Updated: 2024/01/24 17:53:56 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	turn_right(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(ROT_SPEED) - data->player->dir_y * sinf(ROT_SPEED);
	data->player->dir_y = old_dir_x * sinf(ROT_SPEED) + data->player->dir_y * cosf(ROT_SPEED);
	data->player->plane_x = data->player->plane_x * cos(ROT_SPEED) - data->player->plane_y * sin(ROT_SPEED);
	data->player->plane_y = old_plane_x * sin(ROT_SPEED) + data->player->plane_y * cos(ROT_SPEED);
	printf("Turn right\n");
}
//Uses the keyboard
void	turn_left(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;
	
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(-ROT_SPEED) - data->player->dir_y * sinf(-ROT_SPEED);
	data->player->dir_y = old_dir_x * sinf(-ROT_SPEED) + data->player->dir_y * cosf(-ROT_SPEED);
	data->player->plane_x = data->player->plane_x * cos(-ROT_SPEED) - data->player->plane_y * sin(-ROT_SPEED);
	data->player->plane_y = old_plane_x * sin(-ROT_SPEED) + data->player->plane_y * cos(-ROT_SPEED);
	printf("Turn left\n");
}
//Uses the mouse
void	look_left(t_data *data, float x)
{
	float	old_dir_x;
	float	old_plane_x;
	
	x *= 0.005;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(-ROT_SPEED) - data->player->dir_y * sinf(-ROT_SPEED);
	data->player->dir_y = old_dir_x * sinf(-ROT_SPEED) + data->player->dir_y * cosf(-ROT_SPEED);
	data->player->plane_x = data->player->plane_x * cos(-ROT_SPEED) - data->player->plane_y * sin(-ROT_SPEED);
	data->player->plane_y = old_plane_x * sin(-ROT_SPEED) + data->player->plane_y * cos(-ROT_SPEED);
	printf("Look left\n");
}

void	look_right(t_data *data, float x)
{
	float	old_dir_x;
	float	old_plane_x;

	x *= 0.005;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(ROT_SPEED) - data->player->dir_y * sinf(ROT_SPEED);
	data->player->dir_y = old_dir_x * sinf(ROT_SPEED) + data->player->dir_y * cosf(ROT_SPEED);
	data->player->plane_x = data->player->plane_x * cos(ROT_SPEED) - data->player->plane_y * sin(ROT_SPEED);
	data->player->plane_y = old_plane_x * sin(ROT_SPEED) + data->player->plane_y * cos(ROT_SPEED);
	printf("Look right\n");
}