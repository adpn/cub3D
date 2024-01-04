/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupin <adupin@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:30:46 by adupin            #+#    #+#             */
/*   Updated: 2024/01/04 16:52:01 by adupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Return the number of words in a string.
static size_t	nb_word(char const *s, char *charset)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s && s[i])
	{
		if (!ft_strchr(charset, s[i]))
		{
			nb++;
			while (s[i] && !ft_strchr(charset, s[i]))
				i++;
		}
		else
			i++;
	}
	return (nb);
}

// Return the length of a word.
static size_t	ln_word(char const *s, char *charset, size_t i)
{
	size_t	len;

	len = 0;
	while (s[i] && !ft_strchr(charset, s[i]))
	{
		i++;
		len++;
	}
	return (len);
}

// Free a NULL or 0 terminated array.
static void	*ft_free(char **strs, size_t j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
	return (NULL);
}

// Split a string into an array of strings.
char	**ft_split_charset(char const *s, char *charset)
{
	ssize_t	size;
	char	**strs;
	ssize_t	i;
	ssize_t	j;
	size_t	len;

	size = nb_word(s, charset);
	strs = malloc((size + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < size)
	{
		while (ft_strchr(charset, s[i]))
			i++;
		len = ln_word(s, charset, i);
		strs[j] = ft_substr(s, i, len);
		if (!strs[j])
			if (!ft_free(strs, j))
				return (NULL);
		i += len;
	}
	strs[j] = NULL;
	return (strs);
}
