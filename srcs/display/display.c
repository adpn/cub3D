/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/29 12:40:50 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	print_texture(t_data *data) // to remove, was just for testing
{
	int color;
	void	*img;

	img = mlx_new_image(data->mlx_ptr, 64, 64);
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			color = get_pixel_color(data->east_img, x, y);
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, color);
		}
	}
	//mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img, 0, 0);
}

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
		ray->camera_x = 2 * x / (float)WINDOW_WIDTH - 1;
		ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;

		ray->map_x = (int)player->pos_x;
		ray->map_y = (int)player->pos_y;

		ray->del_dist_x = fabsf(1 / ray->dir_x);
		ray->del_dist_y = fabsf(1 / ray->dir_y);

		//length of ray from current position to next x or y-side
		float	perpWallDist; //perpendicular wall??
		float sideDistX;
		float sideDistY;
		int stepX;
     	int stepY;
		int hit = 0; //was there a wall hit?
      	int side; //was a NS or a EW wall hit?

		if (ray->dir_x < 0)
		{
			stepX = -1;
			sideDistX = (player->pos_x - ray->map_x) * ray->del_dist_x;
		}
		else
		{
        	stepX = 1;
        	sideDistX = (ray->map_x + 1.0 - player->pos_x) * ray->del_dist_x;
		}
		if (ray->dir_y < 0)
		{
        	stepY = -1;
        	sideDistY = (player->pos_y - ray->map_y) * ray->del_dist_y;
		}
      	else
		{
			stepY = 1;
        	sideDistY = (ray->map_y + 1.0 - player->pos_y) * ray->del_dist_y;
		}
		//perform DDA
		//printf("DDA BEGIN\n");
		while (!hit)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += ray->del_dist_x;
				ray->map_x += stepX;
				side = 0; //side need to have 4 possible values not 2
			}
			else
			{
				sideDistY += ray->del_dist_y;
				ray->map_y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[ray->map_y][ray->map_x] == '1'
				|| (data->map[ray->map_y][ray->map_x] == 'D' && (fabs(ray->map_x - player->pos_x) > 3 || fabs(ray->map_y - player->pos_y) > 3)))
				hit = 1;
    	}
		//printf("DDA FINISH\n");
		if (side == 0)
			perpWallDist = (sideDistX - ray->del_dist_x);
      	else
	  		perpWallDist = (sideDistY - ray->del_dist_y);

		//Calculate height of line to draw on screen
      int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
      if(drawEnd >= WINDOW_HEIGHT)
	  	drawEnd = WINDOW_HEIGHT - 1;

	// int	color;
	// if (side == 1)
	// 	color = get_pixel_color(data->north_img, 1, 1);
	// else
	// 	color = get_pixel_color(data->west_img, 1, 1);
	// print_line(data->screen, x, drawStart, drawEnd, color);


	float	wall_x;
	if (side == 0)
		wall_x = player->pos_y + perpWallDist * ray->dir_y;
    else
		wall_x = player->pos_x + perpWallDist * ray->dir_x;
    wall_x -= floor((wall_x)); //round to inferior integer

	int tex_x = (int)(wall_x * (float)data->north_img->img_width); //need to remove data->north_img->img_width and put real value
	if (side == 0 && ray->dir_x > 0)
		tex_x = data->north_img->img_width - tex_x - 1;
	if (side == 1 && ray->dir_y < 0)
		tex_x = data->north_img->img_width - tex_x - 1;
	
	float step = 1.0 * data->north_img->img_height / lineHeight;
	float texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
	for (int y = drawStart; y < drawEnd; y++)
      {
        int texY = (int)texPos & (data->north_img->img_height - 1);
		texPos += step;
		if (tex_x < 0 || texY < 0 || tex_x > data->north_img->img_width || texY > data->north_img->img_height)
			write(1, "Wrong\n", 6);
		else
			mlx_pixel_put_img(data->screen, x, y, get_pixel_color(data->north_img, tex_x, texY));
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
