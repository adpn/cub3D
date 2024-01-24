/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mgmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:51:32 by adupin            #+#    #+#             */
/*   Updated: 2024/01/24 17:33:15 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

int	keydown(int keycode, t_data *data)
{
	if (!data->input.mouse_locked)
		return (0);
	if (keycode == KEY_W)
		data->input.w = 1;
	if (keycode == KEY_A)
		data->input.a = 1;
	if (keycode == KEY_S)
		data->input.s = 1;
	if (keycode == KEY_D)
		data->input.d = 1;
	if (keycode == KEY_LEFT)
		data->input.left = 1;
	if (keycode == KEY_RIGHT)
		data->input.right = 1;
	if (keycode == KEY_ESC)
		end(data);
	return (0);
}

int	keyup(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->input.w = 0;
	if (keycode == KEY_A)
		data->input.a = 0;
	if (keycode == KEY_S)
		data->input.s = 0;
	if (keycode == KEY_D)
		data->input.d = 0;
	if (keycode == KEY_LEFT)
		data->input.left = 0;
	if (keycode == KEY_RIGHT)
		data->input.right = 0;
	return (0);
}

int mouse_move(int x, int y, t_data *data)
{
	//printf("x: %i, y: %i\n", x, y);
	if (!data->input.mouse_locked)
		return (0);
	if (x > 0)
		look_right(data, x);
	else
		look_left(data, abs(x));
	(void)y;
	mlx_mouse_move(data->mlx_win, 0, 0);
	return (0);
}

int	send_change(t_data *data)
{
	if (!data->input.mouse_locked)
		return (0);
	if (data->input.w)
		move_forward(data);
	if (data->input.s)
		move_backward(data);
	if (data->input.d)
		move_right(data);
	if (data->input.a)
		move_left(data);
	if (data->input.left)
		turn_left(data);
	if (data->input.right)
		turn_right(data);
	update(data);
	return (0);
}

int mouse_click(int button, int x, int y, t_data *data)
{
	if (button == RIGHT_CLICK)
	{
		if (data->input.mouse_locked)
		{
			data->input.mouse_locked = 0;
			mlx_mouse_show();
		}
		else
		{
			data->input.mouse_locked = 1;
			mlx_mouse_hide();
		}
		printf("Right click\n");
	}
	printf("Click x: %i, y: %i\n", x, y);
	(void)data;
	return (0);
}
