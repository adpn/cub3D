/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:04:29 by adupin            #+#    #+#             */
/*   Updated: 2024/02/01 17:07:25 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "cub3d.h"

/* display.c */
int		end(t_data *data);
int		update(t_data *data);

/* minimap.c */
int		generate_minimap(t_data *data);
void	update_minimap(t_data *data);

/* color.c */
int		get_pixel_color(t_img_info *img, int x, int y);
int		create_trgb(int t, int r, int g, int b);

/* mlx_helper.c */
void	mlx_pixel_put_img(t_img_info *img, int x, int y, int color);
void	mlx_true_pixel_put_img(t_img_info *img, int x, int y, int color);
void	mlx_img_put_img(t_img_info *src, t_img_info *dest, int x, int y);
void	print_line(t_img_info *img, int x, int start, int end, int color);
void	print_rect(t_img_info *img, int x, int y, int width, int height, int color);

/* setup.c & textures.c & images.c */
void	img_to_addr(t_img_info *img);
int		setup_textures(t_data *data);
int		malloc_img(t_data *data);
void	revert_all_img(t_data *data);

/* weapon_actions.c */
void	gun_hands(t_data *data);

/* move.c */
void	move_forward(t_player *player, char **map);
void	move_backward(t_player *player, char **map);
void	move_right(t_player *player, char **map);
void	move_left(t_player *player, char **map);

/* turn_look.c */
void	turn_right(t_player *player);
void	turn_left(t_player *player);
void	look_left(t_player *player, float x);
void	look_right(t_player *player, float x);

/* raycasting.c & single_raycast.c */
void	raycast_for_x(t_data *data, t_player *player, int x, unsigned int anim);
void	ray_init(t_ray *ray, t_player *player, int x);
void	first_step_calc(t_ray *ray, t_player *player);
void	dda(char **map, t_ray *ray, t_player *player);
void	wall_size_calc(t_ray *ray, t_wall *wall);
void	assign_texture(t_data *data, t_ray *ray, t_wall *wall);

/* input_mgmt.c */
int		keydown(int keycode, t_data *data);
int		keyup(int keycode, t_data *data);
int		mouse_move(int x, int y, t_data *data);
int		send_change(t_data *data);
int		mouse_click(int button, int x, int y, t_data *data);

#endif
