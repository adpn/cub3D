/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:04:07 by adupin            #+#    #+#             */
/*   Updated: 2024/01/30 12:04:47 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	ray_init(t_ray *ray, t_player *player, int x)
{
	ray->camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->del_dist_x = fabsf(1 / ray->dir_x);
	ray->del_dist_y = fabsf(1 / ray->dir_y);
}

void	first_step_calc(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->del_dist_x;
	}
	else
	{
    	ray->step_x = 1;
      	ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->del_dist_x;
	}
	if (ray->dir_y < 0)
	{
     	ray->step_y = -1;
      	ray->side_dist_y = (player->pos_y - ray->map_y) * ray->del_dist_y;
	}
	else
	{
		ray->step_y = 1;
     	ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->del_dist_y;
	}
}

void	dda(char **map, t_ray *ray, t_player *player)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->del_dist_x;
			ray->map_x += ray->step_x;
			ray->direction = 0;
		}
		else
		{
			ray->side_dist_y += ray->del_dist_y;
			ray->map_y += ray->step_y;
			ray->direction = 1;
		}
		//Check if ray has hit a wall
		if (map[ray->map_y][ray->map_x] == '1'
			|| (map[ray->map_y][ray->map_x] == 'D' && (fabs(ray->map_x - player->pos_x) > 3 || fabs(ray->map_y - player->pos_y) > 3)))
			hit = 1;
 	}
}

void	wall_size_calc(t_ray *ray, t_wall *wall)
{
    wall->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + WINDOW_HEIGHT / 2;
    if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + WINDOW_HEIGHT / 2;
    if (wall->draw_end >= WINDOW_HEIGHT)
		wall->draw_end = WINDOW_HEIGHT - 1;
}

void	assign_texture(t_data *data, t_ray *ray, t_wall *wall)
{
	if (data->map[ray->map_y][ray->map_x] == 'D')
		wall->texture = data->door_img;
	else if (ray->direction == 0)
	{
		if (ray->step_x < 0)
			wall->texture = data->west_img;
		else
			wall->texture = data->east_img;
	}
	else
	{
		if (ray->step_y < 0)
			wall->texture = data->north_img;
		else
			wall->texture = data->south_img;
	}
}
