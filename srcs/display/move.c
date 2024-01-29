/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:44:35 by adupin            #+#    #+#             */
/*   Updated: 2024/01/29 12:41:24 by adupin           ###   ########.fr       */
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
		&& data->map[(int) y][(int)(x + copysign(WALL_BUFFER, data->player->dir_x))] != '1')
		data->player->pos_x += data->player->dir_x * MOVE_SPEED;
	x = data->player->pos_x;
	y = (data->player->pos_y + data->player->dir_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int)(y + copysign(WALL_BUFFER, data->player->dir_y))][(int) x] != '1')
		data->player->pos_y += data->player->dir_y * MOVE_SPEED;
}

void	move_backward(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x - data->player->dir_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int)(x - copysign(WALL_BUFFER, data->player->dir_x))] != '1')
		data->player->pos_x -= data->player->dir_x * MOVE_SPEED;
	x = data->player->pos_x;
	y = (data->player->pos_y - data->player->dir_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int)(y - copysign(WALL_BUFFER, data->player->dir_y))][(int) x] != '1')
		data->player->pos_y -= data->player->dir_y * MOVE_SPEED;
}

void	move_right(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x + data->player->plane_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int)(x + copysign(WALL_BUFFER, data->player->plane_x))] != '1')
		data->player->pos_x += data->player->plane_x * MOVE_SPEED;
	x = data->player->pos_x;
	y = (data->player->pos_y + data->player->plane_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int)(y + copysign(WALL_BUFFER, data->player->plane_y))][(int) x] != '1')
		data->player->pos_y += data->player->plane_y * MOVE_SPEED;
}

void	move_left(t_data *data)
{
	float	x;
	float	y;

	y = data->player->pos_y;
	x = (data->player->pos_x - data->player->plane_x * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int) y][(int)(x - copysign(WALL_BUFFER, data->player->plane_x))] != '1')
		data->player->pos_x -= data->player->plane_x * MOVE_SPEED;
	x = data->player->pos_x;
	y = (data->player->pos_y - data->player->plane_y * MOVE_SPEED);
	if (data->map[(int) y][(int) x] != '1'
		&& data->map[(int)(y - copysign(WALL_BUFFER, data->player->plane_y))][(int) x] != '1')
		data->player->pos_y -= data->player->plane_y * MOVE_SPEED;
}

