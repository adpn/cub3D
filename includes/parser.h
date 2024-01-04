/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:52:28 by adupin            #+#    #+#             */
/*   Updated: 2024/01/04 18:28:13 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include "utils.h"

char	**ft_split_charset(char const *s, char *charset);
char	*cat_all_in_one(char **list_elements);

int	assign_color(int *color, char **tab);

#endif