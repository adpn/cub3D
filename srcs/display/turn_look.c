/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_look.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:53:43 by adupin            #+#    #+#             */
/*   Updated: 2024/01/31 14:46:39 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	turn_right(t_player *player)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x
		= player->dir_x * cosf(ROT_SPEED) - player->dir_y * sinf(ROT_SPEED);
	player->dir_y
		= old_dir_x * sinf(ROT_SPEED) + player->dir_y * cosf(ROT_SPEED);
	player->plane_x
		= player->plane_x * cos(ROT_SPEED) - player->plane_y * sin(ROT_SPEED);
	player->plane_y
		= old_plane_x * sin(ROT_SPEED) + player->plane_y * cos(ROT_SPEED);
}

//Uses the keyboard
void	turn_left(t_player *player)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x
		= player->dir_x * cosf(-ROT_SPEED) - player->dir_y * sinf(-ROT_SPEED);
	player->dir_y
		= old_dir_x * sinf(-ROT_SPEED) + player->dir_y * cosf(-ROT_SPEED);
	player->plane_x
		= player->plane_x * cos(-ROT_SPEED) - player->plane_y * sin(-ROT_SPEED);
	player->plane_y
		= old_plane_x * sin(-ROT_SPEED) + player->plane_y * cos(-ROT_SPEED);
}

//Uses the mouse
void	look_left(t_player *player, float x)
{
	float	old_dir_x;
	float	old_plane_x;

	x *= 0.002;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x
		= player->dir_x * cosf(-ROT_SPEED) - player->dir_y * sinf(-ROT_SPEED);
	player->dir_y
		= old_dir_x * sinf(-ROT_SPEED) + player->dir_y * cosf(-ROT_SPEED);
	player->plane_x
		= player->plane_x * cos(-ROT_SPEED) - player->plane_y * sin(-ROT_SPEED);
	player->plane_y
		= old_plane_x * sin(-ROT_SPEED) + player->plane_y * cos(-ROT_SPEED);
}

void	look_right(t_player *player, float x)
{
	float	old_dir_x;
	float	old_plane_x;

	x *= 0.002;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x
		= player->dir_x * cosf(ROT_SPEED) - player->dir_y * sinf(ROT_SPEED);
	player->dir_y
		= old_dir_x * sinf(ROT_SPEED) + player->dir_y * cosf(ROT_SPEED);
	player->plane_x
		= player->plane_x * cos(ROT_SPEED) - player->plane_y * sin(ROT_SPEED);
	player->plane_y
		= old_plane_x * sin(ROT_SPEED) + player->plane_y * cos(ROT_SPEED);
}
