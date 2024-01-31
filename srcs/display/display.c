/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/31 14:29:43 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	end(t_data *data)
{
	printf("Bye bye !\n");
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	mlx_destroy_image(data->mlx_ptr, data->screen->img);
	destroy_textures(data);
	free(data->screen);
	free_img(data);
	clear_map(data);
	clear_minimap(data);
	exit(0);
	return (1);
}

// replaced 'tex_y = tex_pos & texture->img_height - 1' with 'tex_y = tex_pos'
void	draw_column(t_data *data, t_wall *wall, int x)
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

	wall = data->wall;
	wall->tex_x = (int)(wall->wall_x * (float)wall->texture->img_width);
	if (data->ray->direction == 0 && data->ray->dir_x > 0)
		wall->tex_x = wall->texture->img_width - wall->tex_x - 1;
	if (data->ray->direction == 1 && data->ray->dir_y < 0)
		wall->tex_x = wall->texture->img_width - wall->tex_x - 1;
	wall->step = 1.0 * wall->texture->img_height / wall->line_height;
	wall->tex_pos = wall->step
		* (wall->draw_start - WIN_HEIGHT / 2 + wall->line_height / 2);
	draw_column(data, wall, x);
}

static void	gun_hands(t_data *data)
{
	t_img_info	*img;
	static int	timer = 0;
	static int	bullets = 8;

	img = data->gun_img;
	if (data->input.space == 1 && bullets && timer < 3)
	{
		bullets--;
		timer = 3;
		data->input.space = 2;
	}
	if (data->input.r == 1)
	{
		bullets = 8;
		timer = 40;
		data->input.r = 2;
	}
	if (timer)
	{
		img = NULL;
		timer--;
		if (timer == 3)
			timer = 0;
		else if (timer < 3)
			img = (data->gun_img + 1);
	}
	if (img)
		mlx_img_put_img(img, data->screen, WIN_WIDTH / 2 - img->img_width / 2,
			WIN_HEIGHT - img->img_height);
}

int	update(t_data *data)
{
	int					x;
	static unsigned int	anim = 0;
	static unsigned	int	count = 0;
	t_player			*player;
	t_ray				*ray;

	ray = data->ray;
	player = data->player;
	count++;
	if (!(count % 10))
		anim++;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ray_init(ray, player, x);
		first_step_calc(ray, player);
		dda(data->map, ray, player);
		if (ray->direction == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->del_dist_x);
      	else
	  		ray->perp_wall_dist = (ray->side_dist_y - ray->del_dist_y);
		wall_size_calc(ray, data->wall);
		print_line(data->screen, x, 0, data->wall->draw_start, data->ceiling_color);
		print_line(data->screen, x, data->wall->draw_end, WIN_HEIGHT, data->floor_color);
		if (ray->direction == 0)
			data->wall->wall_x = player->pos_y + ray->perp_wall_dist * ray->dir_y;
		else
			data->wall->wall_x = player->pos_x + ray->perp_wall_dist * ray->dir_x;
		data->wall->wall_x -= (int)(data->wall->wall_x);
		assign_texture(data, ray, data->wall);
		calc_and_draw_column(data, x);
		if (data->wall->texture != data->door_img && !(ray->map_y % 3) && !(ray->map_x % 2))
		{
			data->wall->texture = data->torch_img + anim % 4;
			calc_and_draw_column(data, x);
		}
		x++;
	}
	gun_hands(data);
	update_minimap(data);
	mlx_img_put_img(data->minimap, data->screen, WIN_WIDTH - data->minimap->img_width - 10, 10);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->screen->img, 0, 0);
	return (1);
}

static void	init_keys_colors(t_data *data)
{
	data->input.w = 0;
	data->input.a = 0;
	data->input.s = 0;
	data->input.d = 0;
	data->input.r = 0;
	data->input.left = 0;
	data->input.right = 0;
	data->input.space = 0;
	data->input.mouse_locked = 1;
	data->ceiling_color = create_trgb(0, data->parser->ceiling_rgb[0],
			data->parser->ceiling_rgb[1], data->parser->ceiling_rgb[2]);
	data->floor_color = create_trgb(0, data->parser->floor_rgb[0],
			data->parser->floor_rgb[1], data->parser->floor_rgb[2]);
}

int	display(t_data *data)
{
	data->screen = malloc(sizeof(t_img_info));
	if (!data->screen)
		return (ft_error("Malloc failed"));
	data->screen->img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!data->screen->img)
		return (free(data->screen), ft_error("Mlx new image failed"));
	data->screen->img_height = WIN_HEIGHT;
	data->screen->img_width = WIN_WIDTH;
	if (generate_minimap(data))
		return (mlx_destroy_image(data->mlx_ptr, data->screen->img),
			free(data->screen), 1);
	init_keys_colors(data);
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
