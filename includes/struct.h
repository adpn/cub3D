/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:05:16 by adupin            #+#    #+#             */
/*   Updated: 2024/01/04 13:04:48 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_path
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_path;

typedef struct	s_data
{
	int		fd;	
	void	*mlx_ptr;
	void	*mlx_win;
	int		ceiling_color[3];
	int		floor_color[3];
	char	**map;
	t_path	*path;
}			t_data;

#endif