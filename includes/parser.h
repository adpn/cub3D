/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvercaem <bvercaem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:28 by adupin            #+#    #+#             */
/*   Updated: 2024/02/05 14:13:44 by bvercaem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

char	**ft_split_charset(char const *s, char *charset);
char	*cat_all_in_one(char **list_elements);

int		assign_color(int *color, char **tab);
int		get_configuration(t_data *data, int fd);
int		get_map(t_data *data, int fd);
int		only_char(char *str, char *charset);
int		check_map(t_data *data);
#endif