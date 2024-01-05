/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:28 by adupin            #+#    #+#             */
/*   Updated: 2024/01/05 16:59:29 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include "utils.h"

char	**ft_split_charset(char const *s, char *charset);
char	*cat_all_in_one(char **list_elements);

int	assign_color(int *color, char **tab);
int	get_configuration(t_data *data, int fd);
int	get_map(t_data *data, int fd);
#endif