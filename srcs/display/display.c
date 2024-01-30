/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/30 14:57:03 by adupin           ###   ########.fr       */
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

void	draw_column(t_data *data, t_wall *wall, int x)
{
	int	y;
	
	print_line(data->screen, x, 0, wall->draw_start, data->ceiling_color);
	y = wall->draw_start;
	while (y < wall->draw_end)
	{
		wall->tex_y = (int)wall->tex_pos & (wall->texture->img_height - 1);
		wall->tex_pos += wall->step;
		mlx_pixel_put_img(data->screen, x, y, get_pixel_color(wall->texture,
			wall->tex_x, wall->tex_y));
		y++;
	}
	print_line(data->screen, x, wall->draw_end, WINDOW_HEIGHT, data->floor_color);
}

int	update(t_data *data)
{
	t_player	*player;
	t_ray		*ray;

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
		draw_column(data, data->wall, x);
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
	data->ceiling_color = create_trgb(0, data->parser->ceiling_rgb[0], data->parser->ceiling_rgb[1], data->parser->ceiling_rgb[2]);
	data->floor_color = create_trgb(0, data->parser->floor_rgb[0], data->parser->floor_rgb[1], data->parser->floor_rgb[2]);
	mlx_mouse_hide();
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, keydown, data); //need to put all the hook in a function
	mlx_hook(data->mlx_win, ON_KEYUP, 0, keyup, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 0, end, data);
	mlx_hook(data->mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);
	mlx_mouse_hook(data->mlx_win, mouse_click, data);
	mlx_loop_hook(data->mlx_ptr, send_change, data);
	return (0);
}
