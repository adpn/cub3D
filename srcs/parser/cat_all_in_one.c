/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_all_in_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:06:42 by adupin            #+#    #+#             */
/*   Updated: 2024/01/08 16:54:39 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	len_total(char **list_elements)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (list_elements[i])
	{
		len += ft_strlen(list_elements[i]);
		i++;
	}
	return (len);
}

char	*cat_all_in_one(char **list_elements)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((len_total(list_elements) + 1) * sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	while (list_elements[i])
	{
		ft_strlcat(str, list_elements[i], len_total(list_elements) + 2);
		ft_strlcat(str, "", len_total(list_elements) + 2);
		i++;
	}
	return (str);
}
