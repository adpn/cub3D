/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:50:00 by adupin            #+#    #+#             */
/*   Updated: 2024/01/24 17:30:34 by adupin           ###   ########.fr       */
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
	data->parser->north = NULL;
	data->parser->south = NULL;
	data->parser->west = NULL;
	data->parser->east = NULL;
	data->parser->ceiling_rgb[0] = -1;
	data->parser->ceiling_rgb[1] = -1;
	data->parser->ceiling_rgb[2] = -1;
	data->parser->floor_rgb[0] = -1;
	data->parser->floor_rgb[1] = -1;
	data->parser->floor_rgb[2] = -1;
	data->map = NULL;
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
