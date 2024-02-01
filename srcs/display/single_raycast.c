/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:57:05 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/01 13:59:39 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

// replaced 'tex_y = tex_pos & texture->img_height - 1' with 'tex_y = tex_pos'
static void	draw_column(t_data *data, t_wall *wall, int x)
{
	int	y;

	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		wall->tex_y = (int) wall->tex_pos;
		wall->tex_pos += wall->step;
		mlx_pixel_put_img(data->screen, x, y, get_pixel_color(wall->texture,
				wall->tex_x, wall->tex_y));
		y++;
	}
}

static void	calc_and_draw_column(t_data *data, int x)
{
	t_wall	*wall;

	wall = &data->wall;
	wall->tex_x = (int)(wall->wall_x * (float)wall->texture->img_width);
	if (data->ray.direction == 0 && data->ray.dir_x > 0)
		wall->tex_x = wall->texture->img_width - wall->tex_x - 1;
	if (data->ray.direction == 1 && data->ray.dir_y < 0)
		wall->tex_x = wall->texture->img_width - wall->tex_x - 1;
	wall->step = 1.0 * wall->texture->img_height / wall->line_height;
	wall->tex_pos = wall->step
		* (wall->draw_start - WIN_HEIGHT / 2 + wall->line_height / 2);
	draw_column(data, wall, x);
}

static void	raycast_wall_extra(t_data *data, t_ray *ray, int x, int anim)
{
	if (data->wall.texture != data->door_img
		&& !(ray->map_y % 3) && !(ray->map_x % 2))
	{
		data->wall.texture = data->torch_img + anim % 4;
		calc_and_draw_column(data, x);
	}
}

void	raycast_for_x(t_data *data, t_player *player, int x, unsigned int anim)
{
	t_ray	*ray;

	ray = &data->ray;
	ray_init(ray, player, x);
	first_step_calc(ray, player);
	dda(data->map, ray, player);
	if (ray->direction == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->del_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->del_dist_y);
	wall_size_calc(ray, &data->wall);
	print_line(data->screen, x, 0, data->wall.draw_start, data->ceiling_color);
	print_line(data->screen, x, data->wall.draw_end,
		WIN_HEIGHT, data->floor_color);
	if (ray->direction == 0)
		data->wall.wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		data->wall.wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
	data->wall.wall_x -= (int)(data->wall.wall_x);
	assign_texture(data, ray, &data->wall);
	calc_and_draw_column(data, x);
	raycast_wall_extra(data, ray, x, anim);
}
