/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:44:35 by adupin            #+#    #+#             */
/*   Updated: 2024/01/26 16:26:24 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	move_forward(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x + data->player->dir_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int) (x + copysign(0.5, data->player->dir_x))] != '1')
		data->player->pos_x += data->player->dir_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	x = data->player->pos_x;
	y = (data->player->pos_y + data->player->dir_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) (y + copysign(0.5, data->player->dir_y))][(int) x] != '1')
		data->player->pos_y += data->player->dir_y * MOVE_SPEED;
}

void	move_backward(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x - data->player->dir_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int) (x - copysign(0.5, data->player->dir_x))] != '1')
		data->player->pos_x -= data->player->dir_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	x = data->player->pos_x;
	y = (data->player->pos_y - data->player->dir_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) (y - copysign(0.5, data->player->dir_y))][(int) x] != '1')
		data->player->pos_y -= data->player->dir_y * MOVE_SPEED;
}

void	move_right(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x + data->player->plane_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int) (x + copysign(0.5, data->player->plane_x))] != '1')
		data->player->pos_x += data->player->plane_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	x = data->player->pos_x;
	y = (data->player->pos_y + data->player->plane_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) (y + copysign(0.5, data->player->plane_y))][(int) x] != '1')
		data->player->pos_y += data->player->plane_y * MOVE_SPEED;
}

void	move_left(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x - data->player->plane_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int) (x - copysign(0.5, data->player->plane_x))] != '1')
		data->player->pos_x -= data->player->plane_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	x = data->player->pos_x;
	y = (data->player->pos_y - data->player->plane_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) (y - copysign(0.5, data->player->plane_y))][(int) x] != '1')
		data->player->pos_y -= data->player->plane_y * MOVE_SPEED;
}

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

}

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
}
