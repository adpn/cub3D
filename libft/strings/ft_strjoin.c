/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:12:36 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:47 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Concatenate two strings.
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, s1_len + 1);
	ft_strlcat(s + s1_len, s2, s2_len + 1);
	return (s);
}
