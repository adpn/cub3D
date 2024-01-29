/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/29 17:59:51 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	end(t_data *data)
{
	printf("Bye bye !\n");
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_image(data->mlx_ptr, data->screen->img);
	mlx_destroy_image(data->mlx_ptr, data->north_img->img);
	mlx_destroy_image(data->mlx_ptr, data->west_img->img);
	mlx_destroy_image(data->mlx_ptr, data->south_img->img);
	mlx_destroy_image(data->mlx_ptr, data->east_img->img);
	free(data->screen);
	free(data->north_img);
	free(data->west_img);
	free(data->south_img);
	free(data->east_img);
	clear_map(data);
	clear_minimap(data);
	exit(0);
	return (1);
}

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

int	update(t_data *data)
{
	t_player	*player;
	t_ray		*ray;

	ft_memset(data->screen->addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	ray = data->ray;
	player = data->player;

	for (int x = 0; x < WINDOW_WIDTH; x++) // change it with a while loop
	{
		//printf("%i\n", x);
		ray_init(ray, player, x);
		first_step_calc(ray, player);
		dda(data->map, ray, player);

		if (ray->direction == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->del_dist_x);
      	else
	  		ray->perp_wall_dist = (ray->side_dist_y - ray->del_dist_y);
		wall_size_calc(ray, data->wall);
		if (ray->direction == 0)
			data->wall->wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
		else
			data->wall->wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
		data->wall->wall_x -= (int)(data->wall->wall_x);
		assign_texture(data, ray, data->wall);

		data->wall->tex_x = (int)(data->wall->wall_x * (float)data->wall->texture->img_width); //need to remove data->north_img->img_width and put real value
		if (ray->direction == 0 && ray->dir_x > 0)
			data->wall->tex_x = data->wall->texture->img_width - data->wall->tex_x - 1;
		if (ray->direction == 1 && ray->dir_y < 0)
			data->wall->tex_x = data->wall->texture->img_width - data->wall->tex_x - 1;

		data->wall->step = 1.0 * data->wall->texture->img_height / data->wall->line_height;
		data->wall->tex_pos = (data->wall->draw_start - WINDOW_HEIGHT / 2 + data->wall->line_height / 2) * data->wall->step;
		for (int y = data->wall->draw_start; y < data->wall->draw_end; y++)
		{
			data->wall->tex_y = (int)data->wall->tex_pos & (data->wall->texture->img_height - 1);
			data->wall->tex_pos += data->wall->step;
			mlx_pixel_put_img(data->screen, x, y, get_pixel_color(data->wall->texture, data->wall->tex_x, data->wall->tex_y));

		}
	}
// added two minimap fts here
	update_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->screen->img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->minimap->img, WINDOW_WIDTH - data->minimap->img_width - 10, 10);
	return (1);
}

void	init_keys(t_input *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->mouse_locked = 1;
}

int	display(t_data *data)
{
	data->screen = malloc(sizeof(t_img_info));
	if (!data->screen)
		return (ft_error("Malloc failed"));
	data->screen->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->screen->img)
		return (free(data->screen), ft_error("Mlx new image failed"));
	if (generate_minimap(data))
		return (mlx_destroy_image(data->mlx_ptr, data->screen->img),
			free(data->screen), 1);
	init_keys(&data->input);
	img_to_addr(data->screen);
	data->player->plane_y = data->player->dir_x * 0.66;
	data->player->plane_x = -data->player->dir_y * 0.66;
	mlx_mouse_hide();
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, keydown, data); //need to put all the hook in a function
	mlx_hook(data->mlx_win, ON_KEYUP, 0, keyup, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 0, end, data);
	mlx_hook(data->mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);
	mlx_mouse_hook(data->mlx_win, mouse_click, data);
	mlx_loop_hook(data->mlx_ptr, send_change, data);
	return (0);
}
