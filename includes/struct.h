/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:16 by adupin            #+#    #+#             */
/*   Updated: 2024/01/29 12:33:37 by adupin           ###   ########.fr       */
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

typedef struct s_parser
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*door;
	int		ceiling_rgb[3];
	int		floor_rgb[3];
}				t_parser;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;

	float	dir_x;
	float	dir_y;

	float	plane_x;
	float	plane_y;
}				t_player;

typedef struct s_ray //probably need to think about this structure
{
	//Direction vector
	float	dir_x;
	float	dir_y;

	//Current coordinates of the ray in the map
	int		map_x;
	int		map_y;

	// "Real" position of the ray
	float	pos_x;
	float	pos_y;

	//Camera is along the plane, and from where the ray starts
	float	camera_x;
	float	camera_y;

	//Distance to go to the next x side or next y side
	float	del_dist_x;
	float	del_dist_y;

}		t_ray;

typedef struct	s_input
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		mouse_coord[2];
	int		mouse_locked; // 0 = unlocked, 1 = locked
}				t_input;


typedef struct s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	char		**map;
	int			map_size;
	t_parser	*parser;
	t_img_info	*north_img;
	t_img_info	*south_img;
	t_img_info	*west_img;
	t_img_info	*east_img;
	t_img_info	*door_img;
	int			ceiling_color;
	int			floor_color;
	t_ray		*ray;
	t_player	*player;
	t_img_info	*screen;
	t_img_info	*minimap;
	t_input	input;
}			t_data;

#endif
