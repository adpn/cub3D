/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexphil <alexphil@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:40:19 by alexphil          #+#    #+#             */
/*   Updated: 2023/09/11 16:36:32 by alexphil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Apply a function to each character of a string.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	ssize_t	i;

	if (!s || !f)
		return (NULL);
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (s[++i])
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}
