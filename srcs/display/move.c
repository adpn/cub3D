/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:44:35 by adupin            #+#    #+#             */
/*   Updated: 2024/01/19 17:25:48 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	move_forward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x + data->player->dir_x * 0.25);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x += data->player->dir_x * 0.25; //arbitrary speed 0.25
	y = (int)(data->player->pos_y + data->player->dir_y * 0.25);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y += data->player->dir_y * 0.25;
	printf("Go forward\n");
	update(data);
}

void	move_backward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x - data->player->dir_x * 0.25);
	if (data->map[(int)data->player->pos_y][x] == '0')
		data->player->pos_x -= data->player->dir_x * 0.25; //arbitrary speed 0.25
	y = (int)(data->player->pos_y - data->player->dir_y * 0.25);
	if (data->map[y][(int)data->player->pos_x] == '0')
		data->player->pos_y -= data->player->dir_y * 0.25;
	printf("Go backward\n");
	update(data);
}

void	move_right(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player->pos_x + data->player->plane_x * 0.25);
	y = (int)(data->player->pos_y + data->player->plane_y * 0.25);
	if (data->map[y][x] != '0')
		return ;
	printf("Go right\n");
	data->player->pos_x += data->player->plane_x * 0.25; //arbitrary speed 0.25
	data->player->pos_y += data->player->plane_y * 0.25;
	update(data);	
}

void	move_left(t_data *data)
{
	int	x;
	int	y;
	
	x = (int)(data->player->pos_x - data->player->plane_x * 0.25);
	y = (int)(data->player->pos_y - data->player->plane_y * 0.25);
	if (data->map[y][x] != '0')
		return ;
	printf("Go left\n");
	data->player->pos_x -= data->player->plane_x * 0.25; //arbitrary speed 0.25
	data->player->pos_y -= data->player->plane_y * 0.25;
	update(data);	
}

void	turn_right(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(0.25) - data->player->dir_y * sinf(0.25);
	data->player->dir_y = old_dir_x * sinf(0.25) + data->player->dir_y * cosf(0.25);
	data->player->plane_x = data->player->plane_x * cos(0.25) - data->player->plane_y * sin(0.25);
	data->player->plane_y = old_plane_x * sin(0.25) + data->player->plane_y * cos(0.25);
	printf("Turn right\n");
	update(data);

}

void	turn_left(t_data *data)
{
	float	old_dir_x;
	float	old_plane_x;
	
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = data->player->dir_x * cosf(-0.25) - data->player->dir_y * sinf(-0.25);
	data->player->dir_y = old_dir_x * sinf(-0.25) + data->player->dir_y * cosf(-0.25);
	data->player->plane_x = data->player->plane_x * cos(-0.25) - data->player->plane_y * sin(-0.25);
	data->player->plane_y = old_plane_x * sin(-0.25) + data->player->plane_y * cos(-0.25);
	printf("Turn left\n");
	update(data);
}
