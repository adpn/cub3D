/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:51:53 by bvercaem          #+#    #+#             */
/*   Updated: 2024/02/01 13:59:52 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

static int	set_bullets_timer(int *bullets, int amount, int *timer, int ticks)
{
	*bullets = amount;
	*timer = ticks;
	return (2);
}

void	gun_hands(t_data *data)
{
	t_img_info	*img;
	static int	timer = 0;
	static int	bullets = 8;

	img = data->gun_img;
	if (data->input.space == 1 && bullets && timer < 3)
		data->input.space = set_bullets_timer(&bullets, bullets - 1, &timer, 3);
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
