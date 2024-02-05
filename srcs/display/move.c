/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:44:35 by adupin            #+#    #+#             */
/*   Updated: 2024/02/05 14:10:38 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	move_forward(t_player *player, char **map)
{
	float	x;
	float	y;

	y = player->pos_y;
	x = (player->pos_x + player->dir_x * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int) y][(int)(x + copysign(WALL_ZONE, player->dir_x))] != '1')
		player->pos_x += player->dir_x * MOVE_SPEED;
	x = player->pos_x;
	y = (player->pos_y + player->dir_y * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int)(y + copysign(WALL_ZONE, player->dir_y))][(int) x] != '1')
		player->pos_y += player->dir_y * MOVE_SPEED;
}

void	move_backward(t_player *player, char **map)
{
	float	x;
	float	y;

	y = player->pos_y;
	x = (player->pos_x - player->dir_x * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int) y][(int)(x - copysign(WALL_ZONE, player->dir_x))] != '1')
		player->pos_x -= player->dir_x * MOVE_SPEED;
	x = player->pos_x;
	y = (player->pos_y - player->dir_y * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int)(y - copysign(WALL_ZONE, player->dir_y))][(int) x] != '1')
		player->pos_y -= player->dir_y * MOVE_SPEED;
}

void	move_right(t_player *player, char **map)
{
	float	x;
	float	y;

	y = player->pos_y;
	x = (player->pos_x + player->plane_x * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int) y][(int)(x + copysign(WALL_ZONE, player->plane_x))] != '1')
		player->pos_x += player->plane_x * MOVE_SPEED;
	x = player->pos_x;
	y = (player->pos_y + player->plane_y * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int)(y + copysign(WALL_ZONE, player->plane_y))][(int) x] != '1')
		player->pos_y += player->plane_y * MOVE_SPEED;
}

void	move_left(t_player *player, char **map)
{
	float	x;
	float	y;

	y = player->pos_y;
	x = (player->pos_x - player->plane_x * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int) y][(int)(x - copysign(WALL_ZONE, player->plane_x))] != '1')
		player->pos_x -= player->plane_x * MOVE_SPEED;
	x = player->pos_x;
	y = (player->pos_y - player->plane_y * MOVE_SPEED);
	if (map[(int) y][(int) x] != '1'
		&& map[(int)(y - copysign(WALL_ZONE, player->plane_y))][(int) x] != '1')
		player->pos_y -= player->plane_y * MOVE_SPEED;
}
