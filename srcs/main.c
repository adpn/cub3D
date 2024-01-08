/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:30:05 by adupin            #+#    #+#             */
/*   Updated: 2024/01/08 16:54:20 by adupin           ###   ########.fr       */
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

	printf("North: %s\n", data->path->north);
	printf("South: %s\n", data->path->south);
	printf("East: %s\n", data->path->east);
	printf("West: %s\n", data->path->west);
	printf("Ceiling: %d %d %d\n", data->ceiling_color[0],
		data->ceiling_color[1], data->ceiling_color[2]);
	printf("Floor: %d %d %d\n", data->floor_color[0],
		data->floor_color[1], data->floor_color[2]);
	printf("Map:\n");
	i = 0;
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

void	free_path(t_data *data)
{
	t_path	*path;

	path = data->path;
	if (path->north)
		free(path->north);
	if (path->south)
		free(path->south);
	if (path->west)
		free(path->west);
	if (path->east)
		free(path->east);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_path	path;

	if (argc != 2)
		return (ft_error("Wrong number of arguments"));
	if (!check_extension(argv[1]) || ft_strlen(argv[1]) < 5)
		return (ft_error("Wrong file extension"));
	data.fd = open(argv[1], O_RDONLY);
	if (data.fd == -1)
		return (ft_error("Can't open file"));
	data.path = &path;
	if (parser(&data, data.fd))
		return (free_path(&data), 1);
	printf_parser(&data);
	free_path(&data);
	clear_map(&data);
	printf("All good\n");
	return (0);
}
