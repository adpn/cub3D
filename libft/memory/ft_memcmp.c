/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:47:02 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:39:24 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compare byte string.
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ps1;
	const char	*ps2;
	size_t		i;

	ps1 = s1;
	ps2 = s2;
	i = 0;
	while (i < n && ps1[i] == ps2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)ps1[i] - (unsigned char)ps2[i]);
}
