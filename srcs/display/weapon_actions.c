/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:51:53 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/05 11:43:42 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	assign_shoot_hit(t_data *data, int x)
{
	if (x != WIN_WIDTH / 2)
		return ;
	data->ray.shoot_map_x = data->ray.map_x;
	data->ray.shoot_map_y = data->ray.map_y;
}

static int	set_bullets_timer(int *bullets, int amount, int *timer, int ticks)
{
	*bullets = amount;
	*timer = ticks;
	return (2);
}

static void	shoot_bullet(t_data *data, int *bullets, int *timer)
{
	data->input.space = set_bullets_timer(bullets, *bullets - 1, timer, 3);
	if (data->map[data->ray.shoot_map_y][data->ray.shoot_map_x] == 'D')
		data->map[data->ray.shoot_map_y][data->ray.shoot_map_x] = '0';
	if (data->map[data->ray.shoot_map_y][data->ray.shoot_map_x] == 'T')
		data->map[data->ray.shoot_map_y][data->ray.shoot_map_x] = '1';
}

void	gun_hands(t_data *data)
{
	t_img_info	*img;
	static int	timer = 0;
	static int	bullets = 8;

	img = data->gun_img;
	if (data->input.space == 1 && bullets && timer < 3)
		shoot_bullet(data, &bullets, &timer);
	if (data->input.r == 1)
		data->input.r = set_bullets_timer(&bullets, 8, &timer, 50);
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
