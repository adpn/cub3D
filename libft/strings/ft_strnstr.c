/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:03:17 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:37:35 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Find a substring in a string within a given length.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	ssize_t	i;

	if (!haystack && !len)
		return (NULL);
	i = -1;
	n_len = ft_strlen(needle);
	if (!n_len)
		return ((char *)haystack);
	while (haystack[++i] && i + n_len <= len)
		if (!ft_strncmp(&haystack[i], needle, n_len))
			return ((char *)&haystack[i]);
	return (0);
}
