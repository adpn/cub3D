/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:30:05 by adupin            #+#    #+#             */
/*   Updated: 2024/01/25 19:00:57 by bvercaem         ###   ########.fr       */
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

	printf("North: %s\n", data->input->north);
	printf("South: %s\n", data->input->south);
	printf("East: %s\n", data->input->east);
	printf("West: %s\n", data->input->west);
	printf("Ceiling: %d %d %d\n", data->input->ceiling_rgb[0],
		data->input->ceiling_rgb[1], data->input->ceiling_rgb[2]);
	printf("Floor: %d %d %d\n", data->input->floor_rgb[0],
		data->input->floor_rgb[1], data->input->floor_rgb[2]);
	printf("Map:\n");
	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

void	free_input(t_data *data)
{
	t_input	*input;

	input = data->input;
	if (input->north)
		free(input->north);
	if (input->south)
		free(input->south);
	if (input->west)
		free(input->west);
	if (input->east)
		free(input->east);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_input		input;
	t_ray		ray;
	t_player	player;
	int			fd;

	if (argc != 2)
		return (ft_error("Wrong number of arguments"));
	if (!check_extension(argv[1]) || ft_strlen(argv[1]) < 5)
		return (ft_error("Wrong file extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error("Cannot open file"));
	data.input = &input;
	data.ray = &ray;
	data.player = &player;
	if (parser(&data, fd))
		return (free_input(&data), 1);
	printf_parser(&data);
	if (setup(&data))
		return (free_input(&data), clear_map(&data), 1);
	free_input(&data);
	if (display(&data))
		return (clear_map(&data), clear_minimap(&data), 1); // probably has to free other stuff
	mlx_loop(data.mlx_ptr);
	printf("All good\n");
	return (0);
}
