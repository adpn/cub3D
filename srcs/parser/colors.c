/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:22:52 by adupin            #+#    #+#             */
/*   Updated: 2024/01/08 12:24:14 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Return 1 if str contains only char from charset, 0 otherwise
int	only_char(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(charset, str[i]))
			return (0);
		i++;
	}
	return (1);	
}

static int	assign_numbers(int *color, char **tab)
{
	color[0] = ft_atoi(tab[0]);
	color[1] = ft_atoi(tab[1]);
	color[2] = ft_atoi(tab[2]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0
		|| color[1] > 255 || color[2] < 0 || color[2] > 255)
		return (1);
	return (0);
}

//Return 0 if ok, 1 if malloc fails, 2 if bad input
int	assign_color(int *color, char **tab)
{
	char	*clean_line;
	char	**comma_split;

	if (color[0] != -1 || color[1] != -1 || color[2] != -1)
		return (ft_error("Color already assigned")); 
	clean_line = cat_all_in_one(tab);
	if (!clean_line)
		return (ft_error("Malloc failed"));
	if (!only_char(&clean_line[1], ",0123456789") || ft_count(&clean_line[1], ',') != 2)
		return (free(clean_line), ft_error("Forbidden character in RGB value"), 1);
	comma_split = ft_split(&clean_line[1], ',');
	if (!comma_split)
		return (free(clean_line), ft_error("Malloc failed"));
	if (assign_numbers(color, comma_split))
		return (free(clean_line), ft_free_split(comma_split), ft_error("Wrong RGB value"));
	free(clean_line);
	ft_free_split(comma_split);
	return (0);
}
