/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:30:05 by adupin            #+#    #+#             */
/*   Updated: 2024/01/29 16:17:30 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *filename)
{
	if (ft_strnstr(&filename[ft_strlen(filename) - 4], ".cub", 4) != NULL)
		return (1);
	return (0);
}

int	ft_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	printf_parser(t_data *data)
{
	int	i;

	printf("North: %s\n", data->parser->north);
	printf("South: %s\n", data->parser->south);
	printf("East: %s\n", data->parser->east);
	printf("West: %s\n", data->parser->west);
	printf("Door: %s\n", data->parser->door);
	printf("Ceiling: %d %d %d\n", data->parser->ceiling_rgb[0],
		data->parser->ceiling_rgb[1], data->parser->ceiling_rgb[2]);
	printf("Floor: %d %d %d\n", data->parser->floor_rgb[0],
		data->parser->floor_rgb[1], data->parser->floor_rgb[2]);
	printf("Map:\n");
	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

void	free_parser(t_data *data)
{
	t_parser	*parser;

	parser = data->parser;
	if (parser->north)
		free(parser->north);
	if (parser->south)
		free(parser->south);
	if (parser->west)
		free(parser->west);
	if (parser->east)
		free(parser->east);
	if (parser->door)
		free(parser->door);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_parser	parser_struct;
	t_ray		ray;
	t_player	player;
	t_wall	wall;
	int			fd;

	if (argc != 2)
		return (ft_error("Wrong number of arguments"));
	if (!check_extension(argv[1]) || ft_strlen(argv[1]) < 5)
		return (ft_error("Wrong file extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error("Cannot open file"));
	data.parser = &parser_struct;
	data.ray = &ray;
	data.player = &player;
	data.wall = &wall;
	if (parser(&data, fd))
		return (free_parser(&data), 1);
	printf_parser(&data);
	if (setup(&data))
		return (free_parser(&data), clear_map(&data), 1);
	free_parser(&data);
	if (display(&data))
		return (clear_map(&data), clear_minimap(&data), 1); // probably has to free other stuff
	mlx_loop(data.mlx_ptr);
	printf("All good\n");
	return (0);
}
