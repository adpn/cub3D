/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:50:00 by adupin            #+#    #+#             */
/*   Updated: 2024/01/26 13:27:55 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
Line example:
F 220,     100, 1    0
tab = F/220,/100,/1/0
split = F 220/       100/ 1     0

F 220,100, 1 02
tab = F/220,100,/1/02

*/

void	init_value(t_data *data)
{
	data->input->north = NULL;
	data->input->south = NULL;
	data->input->west = NULL;
	data->input->east = NULL;
	data->input->door = NULL;
	data->input->ceiling_rgb[0] = -1;
	data->input->ceiling_rgb[1] = -1;
	data->input->ceiling_rgb[2] = -1;
	data->input->floor_rgb[0] = -1;
	data->input->floor_rgb[1] = -1;
	data->input->floor_rgb[2] = -1;
	data->map = NULL;
	data->minimap = NULL;
}

int	parser(t_data *data, int fd)
{
	init_value(data);
	if (get_configuration(data, fd))
		return (close(fd), 1);
	if (get_map(data, fd))
		return (close(fd), 1);
	close(fd);
	if (check_map(data))
		return (clear_map(data), 1);
	return (0);
}
