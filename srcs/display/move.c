/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:44:35 by adupin            #+#    #+#             */
/*   Updated: 2024/01/22 10:58:34 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	move_forward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x + data->player->dir_x * MOVE_SPEED);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x += data->player->dir_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	y = (int)(data->player->pos_y + data->player->dir_y * MOVE_SPEED);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y += data->player->dir_y * MOVE_SPEED;
	printf("Go forward\n");
}

void	move_backward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x - data->player->dir_x * MOVE_SPEED);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x -= data->player->dir_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	y = (int)(data->player->pos_y - data->player->dir_y * MOVE_SPEED);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y -= data->player->dir_y * MOVE_SPEED;
	printf("Go backward\n");
}

void	move_right(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x + data->player->plane_x * MOVE_SPEED);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x += data->player->plane_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	y = (int)(data->player->pos_y + data->player->plane_y * MOVE_SPEED);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y += data->player->plane_y * MOVE_SPEED;	
	printf("Go right\n");
}

void	move_left(t_data *data)
{
	int	x;
	int	y;
	
	x = (int)(data->player->pos_x - data->player->plane_x * MOVE_SPEED);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x -= data->player->plane_x * MOVE_SPEED; //arbitrary speed MOVE_SPEED
	y = (int)(data->player->pos_y - data->player->plane_y * MOVE_SPEED);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y -= data->player->plane_y * MOVE_SPEED;	
	printf("Go left\n");
}

