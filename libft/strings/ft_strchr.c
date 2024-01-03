/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:33:46 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:33:25 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Locate the first occurence of a given character in string.
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char) c)
			return (&((char *)s)[i]);
	if (!(char)c)
		return (&((char *)s)[i]);
	return (0);
}
