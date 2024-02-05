/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:50:00 by adupin            #+#    #+#             */
/*   Updated: 2024/02/05 14:11:44 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_value(t_data *data)
{
	data->parser.north = NULL;
	data->parser.south = NULL;
	data->parser.west = NULL;
	data->parser.east = NULL;
	data->parser.door = NULL;
	data->parser.ceiling_rgb[0] = -1;
	data->parser.ceiling_rgb[1] = -1;
	data->parser.ceiling_rgb[2] = -1;
	data->parser.floor_rgb[0] = -1;
	data->parser.floor_rgb[1] = -1;
	data->parser.floor_rgb[2] = -1;
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
