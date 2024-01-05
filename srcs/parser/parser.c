/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:50:00 by adupin            #+#    #+#             */
/*   Updated: 2024/01/05 17:11:07 by adupin           ###   ########.fr       */
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
	data->path->north = NULL;
	data->path->south = NULL;
	data->path->west = NULL;
	data->path->east = NULL;
	data->ceiling_color[0] = -1;
	data->ceiling_color[1] = -1;
	data->ceiling_color[2] = -1;
	data->floor_color[0] = -1;
	data->floor_color[1] = -1;
	data->floor_color[2] = -1;
	data->map = NULL;
}
 
int	parser(t_data *data, int fd)
{
	init_value(data);
	if (get_configuration(data, fd))
		return (close(fd), 1);
	if (get_map(data, fd))
		return (close(fd), 1);
	
	return (0);
	//close fd here
}