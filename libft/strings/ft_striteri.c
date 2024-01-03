/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:43:58 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:40 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Apply a function to each character of a string.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	ssize_t	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		f(i, &s[i]);
}
