/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/22 17:50:14 by adupin           ###   ########.fr       */
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

void	print_line(t_img_info *img, int x, int start, int end, int color)
{
	while (start < end)
	{
		mlx_pixel_put_img(img, x, start, color);
		start++;		
	}	
}
int	end(t_data *data)
{
	printf("Quit\n");
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
	exit(0);
	return (1);
}

int	send_change(t_data *data)
{
	if (data->key_pressed->w)
		move_forward(data);
	if (data->key_pressed->s)
		move_backward(data);
	if (data->key_pressed->d)
		move_right(data);
	if (data->key_pressed->a)
		move_left(data);
	if (data->key_pressed->left)
		turn_left(data);
	if (data->key_pressed->right)
		turn_right(data);
	update(data);
	return (0);
}

int	update(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	
	ft_memset(data->screen->addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	ray = data->ray;
	player = data->player;
	printf("Player position: %f, %f\n", player->pos_x, player->pos_y);
	printf("Player direction: %f, %f\n", player->dir_x, player->dir_y);
	printf("Player plane: %f, %f\n", player->plane_x, player->plane_y);
	for (int x = 0; x < WINDOW_WIDTH; x++)
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
				side = 0;
			}
			else
			{
				sideDistY += ray->del_dist_y;
				ray->map_y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map[ray->map_y][ray->map_x] != '0')
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

	int	color;
	if (side == 1)
		color = get_pixel_color(data->north_img, 1, 1);
	else
		color = get_pixel_color(data->west_img, 1, 1);
	print_line(data->screen, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->screen->img, 0, 0);
	static int i= 0;
	printf("%i\n", i);
	i++;
	// printf("Printed\n");
	return (1);
}

int	keydown(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_pressed->w = 1;
	if (keycode == KEY_A)
		data->key_pressed->a = 1;
	if (keycode == KEY_S)
		data->key_pressed->s = 1;
	if (keycode == KEY_D)
		data->key_pressed->d = 1;
	if (keycode == KEY_LEFT)
		data->key_pressed->left = 1;
	if (keycode == KEY_RIGHT)
		data->key_pressed->right = 1;
	if (keycode == KEY_ESC)
		end(data);
	return (0);
}

int	keyup(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_pressed->w = 0;
	if (keycode == KEY_A)
		data->key_pressed->a = 0;
	if (keycode == KEY_S)
		data->key_pressed->s = 0;
	if (keycode == KEY_D)
		data->key_pressed->d = 0;
	if (keycode == KEY_LEFT)
		data->key_pressed->left = 0;
	if (keycode == KEY_RIGHT)
		data->key_pressed->right = 0;
	return (0);
}

void	init_keys(t_key_pressed *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

int	display(t_data *data)
{
	data->screen = malloc(sizeof(t_img_info));
	if (!data->screen)
		return (ft_error("Malloc failed"));
	data->key_pressed = malloc(sizeof(t_key_pressed));
	if (!data->key_pressed)
		return (free(data->screen), ft_error("Malloc failed"));
	data->screen->img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->screen->img)
		return (free(data->screen), free(data->key_pressed), ft_error("Mlx new image failed"));
	init_keys(data->key_pressed);
	img_to_addr(data->screen);
	data->player->plane_y = data->player->dir_x * 0.66;
	data->player->plane_x = -data->player->dir_y * 0.66;
	mlx_hook(data->mlx_win, ON_KEYDOWN, 0, keydown, data);
	mlx_hook(data->mlx_win, ON_KEYUP, 0, keyup, data);
	mlx_hook(data->mlx_win, ON_DESTROY, 0, end, data);
	mlx_loop_hook(data->mlx_ptr, send_change, data);
	return (0);
}
