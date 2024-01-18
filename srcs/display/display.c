/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:54:25 by adupin            #+#    #+#             */
/*   Updated: 2024/01/18 17:19:47 by adupin           ###   ########.fr       */
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

int	display(t_data *data)
{
	t_img_info new_img;
	t_player	*player;
	t_ray		*ray;
	
	ray = data->ray;
	player = data->player;
	print_texture(data);
	player->plane_x = 0.66; // only for testing
	player->plane_y = 0;
	printf("Player position: %f, %f\n", player->pos_x, player->pos_y);
	printf("Player direction: %f, %f\n", player->dir_x, player->dir_y);
	printf("Player plane: %f, %f\n", player->plane_x, player->plane_y);
	new_img.img = mlx_new_image(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	img_to_addr(&new_img);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		printf("%i\n", x);
		ray->camera_x = 2 * x / (float)SCREEN_WIDTH - 1;
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
		printf("DDA BEGIN\n");
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
		printf("DDA FINISH\n");
		if (side == 0)
			perpWallDist = (sideDistX - ray->del_dist_x);
      	else
	  		perpWallDist = (sideDistY - ray->del_dist_y);

		//Calculate height of line to draw on screen
      int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
      if(drawEnd >= SCREEN_HEIGHT)
	  	drawEnd = SCREEN_HEIGHT - 1;

	int	color;
	if (side == 1)
		color = get_pixel_color(data->north_img, 1, 1);
	else
		color = get_pixel_color(data->west_img, 1, 1);
	print_line(&new_img, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, new_img.img, 0, 0);
	printf("Printed\n");
	return (1);
}
