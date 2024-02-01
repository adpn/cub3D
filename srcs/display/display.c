/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/02/01 13:57:20 by bvercaem         ###   ########.fr       */
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

int	update(t_data *data)
{
	int					x;
	static unsigned int	anim = 0;
	static unsigned int	count = 0;
	t_player			*player;
	t_ray				*ray;

	ray = &data->ray;
	player = &data->player;
	count++;
	if (!(count % 10))
		anim++;
	x = 0;
	while (x < WIN_WIDTH)
	{
		raycast_for_x(data, player, x, anim);
		x++;
	}
	gun_hands(data);
	update_minimap(data);
	mlx_img_put_img(data->minimap, data->screen,
		WIN_WIDTH - data->minimap->img_width - 10, 10);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->screen->img, 0, 0);
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
	data->ceiling_color = create_trgb(0, data->parser.ceiling_rgb[0],
			data->parser.ceiling_rgb[1], data->parser.ceiling_rgb[2]);
	data->floor_color = create_trgb(0, data->parser.floor_rgb[0],
			data->parser.floor_rgb[1], data->parser.floor_rgb[2]);
}

static void	set_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, keydown, data);
	mlx_hook(data->mlx_win, ON_KEYUP, 0, keyup, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 0, end, data);
	mlx_hook(data->mlx_win, ON_MOUSEMOVE, 0, mouse_move, data);
	mlx_mouse_hook(data->mlx_win, mouse_click, data);
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
	data->player.plane_y = data->player.dir_x * 0.66;
	data->player.plane_x = -data->player.dir_y * 0.66;
	mlx_mouse_hide();
	set_hooks(data);
	mlx_loop_hook(data->mlx_ptr, send_change, data);
	return (0);
}
