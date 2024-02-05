/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:30:05 by adupin            #+#    #+#             */
/*   Updated: 2024/02/05 12:41:39 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *filename)
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

static void	free_parser(t_data *data)
{
	t_parser	*parser;

	parser = &data->parser;
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
	int			fd;

	if (argc != 2)
		return (ft_error("Wrong number of arguments"));
	if (!check_extension(argv[1]) || ft_strlen(argv[1]) < 5)
		return (ft_error("Wrong file extension"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error("Cannot open file"));
	if (parser(&data, fd))
		return (free_parser(&data), 1);
	if (setup(&data))
		return (free_parser(&data), clear_map(&data), 1);
	free_parser(&data);
	if (display(&data))
		return (clear_map(&data), destroy_textures(&data), free_img(&data),
			mlx_destroy_window(data.mlx_ptr, data.mlx_win), 1);
	mlx_loop(data.mlx_ptr);
	return (1);
}

/*	MEMORY:
(doesn't include single-function-use (e.g. 'clean_line' in 'assign_color'))

[thing]			[location]			[allocation(main)]	[how to free]

parser strs		data->parser.*		parser()			free_parser()
map				data->map			parser()			clear_map()
imgs(7)			data->*				setup()				free_img()
textures		data->*				setup()				destroy_textures()
window			data->mlx_win		setup()				mlx_destroy_window()
screen			data->screen		display()			free()
screen_img		data->screen->img	display()			mlx_destroy_image()
minimap			data->minimap		display()			clear_minimap()
minimap_img		data->minimap->img	display()			clear_minimap()

i think it's all good maybe hypothetically! */
