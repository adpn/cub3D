/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:16 by adupin            #+#    #+#             */
/*   Updated: 2024/01/13 17:12:46 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_img_info
{
	void	*img;
	int	img_width;
	int	img_height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_info;

typedef struct s_path
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_path;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
	int		ceiling_color[3];
	int		floor_color[3];
	char	**map;
	t_path	*path;
	t_img_info	*north_img;
	t_img_info	*south_img;
	t_img_info	*west_img;
	t_img_info	*east_img;
}			t_data;

#endif