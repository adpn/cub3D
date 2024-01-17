/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:16 by adupin            #+#    #+#             */
/*   Updated: 2024/01/17 17:15:11 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_img_info
{
	void	*img;
	int		img_width;
	int		img_height;
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

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
}				t_player;

typedef struct s_ray
{
	//Direction vector
	float	dir_x;
	float	dir_y;
	
	float	plane_x;
	float	plane_y;
	
	//Current coordinates of the ray in the map
	int		map_x;
	int		map_y;
	
	// "Real" position of the ray 
	float	pos_x;
	float	pos_y;

}		t_ray;


typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			ceiling_color[3];
	int			floor_color[3];
	char		**map;
	t_path		*path;
	t_img_info	*north_img;
	t_img_info	*south_img;
	t_img_info	*west_img;
	t_img_info	*east_img;
}			t_data;

#endif