/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:30:40 by adupin            #+#    #+#             */
/*   Updated: 2024/01/19 11:46:50 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free, exit
# include <unistd.h> // read, write, close
# include <fcntl.h> // open 
# include <string.h> // strerror
# include <errno.h> // perror
# include <math.h>
# include <mlx.h>
# include "struct.h"

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480

enum e_keys{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53
};

int		ft_error(char *str);
int		parser(t_data *data, int fd);
void	printf_parser(t_data *data);
void	clear_map(t_data *data);
int		setup(t_data *data);
int		display(t_data *data);
#endif
